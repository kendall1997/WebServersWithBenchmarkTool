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

/* We include the header files defined by us which are required for the create operations. 
 */
#include <mythread.h>
#include <mythread_q.h>

/* To be able to use getttid(), we define a function for ourselves that 
   directly references the system call.
 */
#include <sys/syscall.h>
#include <sys/types.h>

#define CLONE_SIGNAL (CLONE_SIGHAND | CLONE_THREAD)

/* The mythread_detach() function.
   
 */
int mythread_detach(mythread_t thread_ID)
{
    // mythread_private_t *target;

    kill(thread_ID.tid, SIGCONT);

    return 0;
}
