/* Single Author info:
 *      sskanitk   Salil S Kanitkar
 * Group info:
 *      jhshah     Jitesh H Shah
 *      sskanitk  Salil S Kanitkar
 *      ajalgao    Aditya A Jalgaonkar
 */

#define _GNU_SOURCE /* See feature_test_macros(7) */

#include <malloc.h>
#include <string.h>
#include <stdlib.h>

/* We are explicitly including these files, since the flags required to be passed
 * clone() system call pick up the standard signal values from these header fiiles.
 */
#include <signal.h>
#include <errno.h>
#include <sched.h>

#include <stdio.h>
#include <sys/wait.h>

/* We include the header files defined by us which are required for the create operations. 
 */
#include <mythread.h>
#include <futex.h>
#include <mythread_q.h>

/* To be able to use getttid(), we define a function for ourselves that 
   directly references the system call.
 */
#include <sys/syscall.h>
#include <sys/types.h>

#define CLONE_SIGNAL (CLONE_SIGHAND | CLONE_THREAD)
#define FIBER_STACK 1024 * 64

/* The global extern pointer defined in mythread.h which points to the head node in
   Queue of the Thread Control Blocks. 
 */
mythread_private_t *mythread_q_head;

/* The mythread_create() function.
   This creates a shared process context by using the clone system call.
   We pass the pointer to a wrapper function ( See mythread_wrapper.c ) which in turn 
   sets up the thread environment and then calls the thread function.
   The mythread_attr_t argument can optionally specify the stack size to be used
   the newly created thread.
 */
int mythread_create(mythread_t *new_thread_ID,
                    mythread_attr_t *attr,
                    void *(*start_func)(void *), void *arg)
{

    // void *stack;
    // pid_t pid;

    // /* Allocate the stack */
    // stack = malloc(FIBER_STACK);
    // if (stack == 0)
    // {
    //     perror("malloc: could not allocate stack");
    //     exit(1);
    // }

    // printf("Creating child thread\n");

    // /* Call the clone system call to create the child thread */
    // pid = clone(start_func, (char *)stack + FIBER_STACK,
    //             SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
    // if (pid == -1)
    // {
    //     perror("clone");
    //     exit(2);
    // }

    // printf("created new thread with id: %ld\n", (unsigned long)pid);

    // /* Wait for the child thread to exit */
    // pid = waitpid(pid, 0, 0);
    // if (pid == -1)
    // {
    //     perror("waitpid");
    //     exit(3);
    // }

    // /* Free the stack */
    // free(stack);
    // printf("Child thread returned and stack freed.\n");

    /* pointer to the stack used by the child process to be created by clone later */
    char *child_stack;

    unsigned long stackSize;
    mythread_private_t *new_node;
    pid_t tid;
    // int retval;

    /* This particular piece of code was added as a result of a weird bug encountered in the __futex_down().
     * In 2.6.35 (our kernel version), all threads can access main thread's stack, but
     * on the OS machine, this stack is somehow private to main thread only.
     */
    new_node = (mythread_private_t *)malloc(sizeof(mythread_private_t));
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
        stackSize = attr->stackSize;
    }

    /* posix_memalign aligns the allocated memory at a 64-bit boundry. */
    if (posix_memalign((void **)&child_stack, 8, stackSize))
    {
        printf("posix_memalign failed! \n");
        return -ENOMEM;
    }

    /* We leave space for one invocation at the base of the stack */
    child_stack = child_stack + stackSize - sizeof(sigset_t);

    /* Save the thread_fun pointer and the pointer to arguments in the TCB. */
    new_node->start_func = start_func;
    new_node->args = arg;
    /* Set the state as READY - READY in Q, waiting to be scheduled. */
    new_node->state = READY;

    new_node->returnValue = NULL;
    new_node->blockedForJoin = NULL;
    /* Initialize the tcb's sched_futex to zero. */
    futex_init(&new_node->sched_futex, 0);

    /* Put it in the Q of thread blocks */
    mythread_q_add(new_node);

    /* Call clone with pointer to wrapper function. TCB will be passed as arg to wrapper function. */
    if ((tid = clone((void *)*start_func, (char *)child_stack, SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0)) == -1)

    {
        printf("clone failed! \n");
        printf("ERROR: %s \n", strerror(errno));
        return (-errno);
    }
    // tid = waitpid(tid, 0, 0);
    // if (tid == -1)
    // {
    //     perror("waitpid");
    //     exit(3);
    // }

    /* Save the tid returned by clone system call in the tcb. */
    new_thread_ID->tid = tid;
    new_node->tid = tid;

    printf("create: Finished initialising new thread: %ld\n", (unsigned long)new_thread_ID->tid);

    //tid = kill(tid, SIGCONT);

    tid = kill(tid, SIGSTOP);

    return 0;
}
