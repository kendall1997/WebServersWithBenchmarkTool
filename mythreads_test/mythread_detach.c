#define _GNU_SOURCE

#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sched.h>
#include <mythread.h>
#include <mythread_q.h>
#include <sys/syscall.h>
#include <sys/types.h>

/* The mythread_detach() function.
 */
int pthread_detach(pthread_t thread_ID)
{
    // pid_t t = syscall(SYS_gettid);

    kill(thread_ID, SIGCONT);

    printf("detach: Thread %ld detached\n", thread_ID);
    return 0;
}
