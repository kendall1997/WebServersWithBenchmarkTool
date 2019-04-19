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
int mythread_detach(mythread_t thread_ID)
{

    kill(thread_ID.tid, SIGCONT);

    printf("detach: Thread %d detached\n", thread_ID.tid);
    return 0;
}
