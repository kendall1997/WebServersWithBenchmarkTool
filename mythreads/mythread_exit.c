#define _GNU_SOURCE
#include <mythread.h>
#include <malloc.h>
#include <mythread_q.h>

#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * This function indicates when a thread ends his execution
 */
void mythread_exit(void *value_ptr)
{
    pid_t t = syscall(SYS_gettid);

    mythread_private_t *thread = mythread_q_search(t);

    thread->state = DEFUNCT;
    thread->returnValue = value_ptr;

    /* Don't remove the node from the list yet. We still have to collect the return value */

    if (thread->blockedForJoin != NULL)
    {
        thread->blockedForJoin->state = READY;
    }

    // free(thread->args);

    // setbuf(stdout, NULL);
    printf("THREAD %d EXIT", thread->tid);

    syscall(SYS_exit, 0);
}
