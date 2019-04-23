#define _GNU_SOURCE
#include <mythread.h>
#include <malloc.h>
#include <mythread_q.h>

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

/* See whether anyone is blocking on us for a join. If yes, mark that thread as READY
 * and kill ourselves
 */
void pthread_exit(void *value_ptr)
{
    pid_t t = syscall(SYS_gettid);

    pthread_private_t *thread = pthread_q_search(t);

    thread->state = DEFUNCT;
    thread->returnValue = value_ptr;

    /* Change the state of any thread waiting on us. FIFO dispatcher will do the
     * needful
     */
    if (thread->blockedForJoin != NULL)
    {
        thread->blockedForJoin->state = READY;
    }

    // free(thread->args);

    // setbuf(stdout, NULL);
    printf("THREAD %d EXIT\n\n", thread->tid);

    syscall(SYS_exit, 0);
}
