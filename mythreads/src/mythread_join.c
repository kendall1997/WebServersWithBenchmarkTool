#define _GNU_SOURCE

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

    mythread_private_t *target, *self_ptr;

    pid_t t;

    target = mythread_q_search(target_thread.tid);

    if (target->state == DEFUNCT)
    {
        *status = target->returnValue;
        return 0;
    }

    if (target->blockedForJoin != NULL)
    {
        return -1;
    }

    t = waitpid(target_thread.tid, 0, 0);

    if (t == -1)
    {
        perror("waitpid");
        exit(3);
    }
    printf("Child thread returned and stack freed.\n");

    *status = target->returnValue;
    return 0;
}
