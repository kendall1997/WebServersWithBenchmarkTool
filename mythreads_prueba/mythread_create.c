#define _GNU_SOURCE

#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <sys/wait.h>
#include <mythread.h>
#include <mythread_q.h>
#include <sys/syscall.h>
#include <sys/types.h>

/* The global extern pointer defined in mythread.h which points to the head node in
   Queue of the Thread Control Blocks. 
 */
pthread_private_t *pthread_q_head;
#define FIBER_STACK 1024 * 64

/* The pthread_create() function.
   This creates a shared process context by using the clone system call.
   We pass the pointer to a wrapper function ( See pthread_wrapper.c ) which in turn 
   sets up the thread environment and then calls the thread function.
   The pthread_attr_t argument can optionally specify the stack size to be used
   the newly created thread.
 */
int pthread_create(pthread_t *new_thread_ID, pthread_attr_t *attr, void *start_func, void *arg)
{

    void *child_stack;

    unsigned long stackSize;
    pthread_private_t *new_node;
    pid_t tid;
    // int retval;

    new_node = (pthread_private_t *)malloc(sizeof(pthread_private_t));
    if (new_node == NULL)
    {
        printf("Cannot allocate memory for node\n");
        return -ENOMEM;
    }

    /* If Stack-size argument is not provided, use the SIGSTKSZ as the default stack size
     * Otherwise, extract the stacksize argument.
     */
    if (attr == NULL)
    {
        stackSize = SIGSTKSZ;
    }
    else
    {
        // stackSize = attr->stackSize;
    }

    /* posix_memalign aligns the allocated memory at a 64-bit boundry. */
    if (posix_memalign((void **)&child_stack, 8, stackSize))
    {
        printf("posix_memalign failed! \n");
        return -ENOMEM;
    }

    child_stack = malloc(FIBER_STACK);
    if (child_stack == 0)
    {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    /* We leave space for one invocation at the base of the stack */
    //child_stack = child_stack + stackSize - sizeof(sigset_t);

    new_node->start_func = start_func;
    new_node->args = arg;
    /* Set the state as READY - READY in Q, waiting to be scheduled. */
    new_node->state = READY;

    new_node->returnValue = NULL;
    new_node->blockedForJoin = NULL;

    /* Put it in the Q of thread blocks */
    pthread_q_add(new_node);

    int FLAGS = SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM;

    /* Call clone with pointer to wrapper function. TCB will be passed as arg to wrapper function. */
    tid = clone(start_func, /*(char *)child_stack*/ (char *)child_stack + FIBER_STACK, FLAGS, arg);

    if (tid == -1)
    {
        perror("clone");
        exit(2);
    }

    /* Save the tid returned by clone system call in the pthread_t. */
    new_thread_ID->tid = tid;
    new_node->tid = tid;

    setbuf(stdout, NULL);
    printf("create: Finished initialising new thread: %ld\n", (unsigned long)new_thread_ID->tid);

    kill(tid, SIGSTOP);
    // tid = kill(tid, SIGSTOP);

    return 0;
}
