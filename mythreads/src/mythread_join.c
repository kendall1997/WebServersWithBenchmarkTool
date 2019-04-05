#define _GNU_SOURCE /* See feature_test_macros(7) */

#include <mythread.h>
#include <mythread_q.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Wait on the thread specified by "target_thread". If the thread is DEFUNCT,
 * just collect the return status. Else, wait for the thread to die and then
 * collect the return status
 */
int mythread_join(mythread_t target_thread, void **status)
{
    kill(target_thread.tid, SIGCONT);

    mythread_private_t *target, *self_ptr;

    pid_t t;

    t = waitpid(target_thread.tid, 0, 0);

    if (t == -1)
    {
        perror("waitpid");
        exit(3);
    }
    printf("Child thread returned and stack freed.\n");

    // printf("JOIN FOR ID: %d", target_thread.tid);

    // target = mythread_q_search(target_thread.tid);

    // /* If the thread is already dead, no need to wait. Just collect the return
    //  * value and exit
    //  */

    // if (target->state == DEFUNCT)
    // {
    //     *status = target->returnValue;
    //     return 0;
    // }

    // target->blockedForJoin = self_ptr;
    // printf("Join: Setting state of %ld to %d\n",
    //        (unsigned long)self_ptr->tid, BLOCKED);
    // self_ptr->state = BLOCKED;

    //*status = target->returnValue;
    return 0;
}
