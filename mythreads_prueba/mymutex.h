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

typedef struct pthread_mymutex
{
    pid_t tid;
    int state;
} pthread_mymutex_t;

int pthread_mymutex_init(pthread_mymutex_t *mutex, void *attr);

int pthread_mymutex_lock(pthread_mymutex_t *mutex);

int pthread_mymutex_unlock(pthread_mymutex_t *mutex);

int pthread_mymutex_trylock(pthread_mymutex_t *mutex);

#endif
