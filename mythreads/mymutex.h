#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mythread.h>
#include <sched.h>

#ifndef MYMUTEX_H
#define MYMUTEX_H

#define INIT 0
#define LOCK 1
#define UNLOCK 2

typedef struct mythread_mymutex
{
    pid_t tid;
    int state;
} mythread_mymutex_t;

int mythread_mymutex_init(mythread_mymutex_t *mutex, void *attr);

int mythread_mymutex_lock(mythread_mymutex_t *mutex);

int mythread_mymutex_unlock(mythread_mymutex_t *mutex);

int mythread_mymutex_trylock(mythread_mymutex_t *mutex);

#endif
