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

int *scheduler_type;
int pthread_join(pthread_t target_thread, void **status)
{
    kill(target_thread, SIGCONT);

    if (scheduler_type == FIFO || scheduler_type == LOTTERY)
    {
        kill(target_thread, SIGCONT);
    }

    pthread_private_t *target, *self_ptr;

    pid_t t;

    target = pthread_q_search(target_thread);

    if (target->state == DEFUNCT)
    {
        *status = target->returnValue;
        return 0;
    }

    if (target->blockedForJoin != NULL)
    {
        return -1;
    }

    t = waitpid(target->tid, 0, 0);
    if (t == -1)
    {
        perror("waitpid");
        exit(3);
    }

    //setbuf(stdout, NULL);
    printf("Child thread %d returned and stack freed.\n", target->tid);

    //*status = target->returnValue;

    target->state = DEFUNCT;

    return 0;
}
