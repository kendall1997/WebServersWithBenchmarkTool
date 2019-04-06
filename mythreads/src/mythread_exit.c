/* Single Author info:
 * 	jhshah 	 Jitesh H Shah
 * Group info:
 * 	jhshah	 Jitesh H Shah
 * 	sskanitk Salil S Kanitkar
 * 	ajalgao	 Aditya A Jalgaonkar
 */

#include <mythread.h>
#include <malloc.h>
#include <mythread_q.h>

#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>

/* See whether anyone is blocking on us for a join. If yes, mark that thread as READY
 * and kill ourselves
 */
void mythread_exit(void *value_ptr)
{
    pid_t t = syscall(SYS_gettid);

    mythread_private_t *thread = mythread_q_search(t);

    printf("STATE: %d\n", t);

    thread->state = DEFUNCT;
    thread->returnValue = value_ptr;

    //printf("STATE: %d\n", thread->state);

    //thread->state = DEFUNCT;

    /* Don't remove the node from the list yet. We still have to collect the return value */

    // /* Change the state of any thread waiting on us. FIFO dispatcher will do the
    //  * needful
    //  */
    if (thread->blockedForJoin != NULL)
    {
        thread->blockedForJoin->state = READY;
    }

    free(thread->args);

    syscall(SYS_exit, 0);
    // __mythread_dispatcher(self_ptr);

    /* Suicide */
    // __mythread_do_exit();
}
