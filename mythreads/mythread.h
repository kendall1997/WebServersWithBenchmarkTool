/*
 * mythread.h -- interface of user threads library
 */

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MYTHREAD_H
#define MYTHREAD_H

#define FALSE 0
#define TRUE 1

#define RUNNING 0
#define READY 1   /* Ready to be scheduled */
#define BLOCKED 2 /* Waiting on Join */
#define DEFUNCT 3 /* Dead */

#define FIFO 0
#define SSROUNDROBIN 1
#define LOTTERY 2
#define REAL 3

typedef struct mythread_attr
{
    unsigned long stackSize; /* Stack size to be used by this thread. Default is SIGSTKSZ */
} mythread_attr_t;

/* Thread Handle exposed to the user */
typedef struct mythread
{
    pid_t tid; /* The thread-id of the thread */
} mythread_t;

/* The Actual Thread Control Block structure */
typedef struct mythread_private
{

    pid_t tid;                               /* The thread-id of the thread */
    int state;                               /* the state in which the corresponding thread will be. */
    void *(*start_func)(void *);             /* The func pointer to the thread function to be executed. */
    void *args;                              /* The arguments to be passed to the thread function. */
    void *returnValue;                       /* The return value that thread returns. */
    struct mythread_private *blockedForJoin; /* Thread blocking on this thread */
    struct mythread_private *prev, *next;

} mythread_private_t;

extern int *scheduler_type;

extern mythread_private_t *mythread_q_head; /* The pointer pointing to head node of the TCB queue */

/*
 * mythread_create - prepares context of new_thread_ID as start_func(arg),
 * attr is ignored right now.
 * Threads are activated (run) according to the number of available LWPs
 * or are marked as ready.
 */
int mythread_create(mythread_t *new_thread_ID,
                    mythread_attr_t *attr,
                    void *start_func,
                    void *arg);

int create(mythread_t *new_thread_ID, mythread_attr_t *attr, void *start_func, void *arg);
/*
 * mythread_join - suspend calling thread if target_thread has not finished,
 * enqueue on the join Q of the target thread, then dispatch ready thread;
 * once target_thread finishes, it activates the calling thread / marks it
 * as ready.
 */
int mythread_join(mythread_t target_thread, void **status);

int mythread_detach(mythread_t thread_ID);

/*
 * mythread_exit - exit thread, awakes joiners on return
 * from thread_func and dequeue itself from run Q before dispatching run->next
 */
void mythread_exit(void *retval);

void mythread_sched(char *scheduler);

/* Private functions */

#endif /* MYTHREAD_H */
