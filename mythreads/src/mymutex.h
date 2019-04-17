/*
 * mythread.h -- interface of user threads library
 */

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mythread.h>
#include <sched.h>

#ifndef MYMUTEX_H
#define mymutex_H

#define FALSE 0
#define TRUE 1

#define INIT 0
#define LOCK 1
#define UNLOCK 2 /* Ready to be scheduled */

typedef struct mythread_mymutex
{
    pid_t tid;
    int state; /* Stack size to be used by this thread. Default is SIGSTKSZ */
} mythread_mymutex_t;

extern mythread_private_t *mythread_q_head; /* The pointer pointing to head node of the TCB queue */

int mythread_mymutex_init(mythread_mymutex_t *mutex, void *attr);

int mythread_mymutex_lock(mythread_mymutex_t *mutex);

int mythread_mymutex_unlock(mythread_mymutex_t *mutex);

int mythread_mymutex_trylock(mythread_mymutex_t *mutex);

#endif /* MYTHREAD_H */
