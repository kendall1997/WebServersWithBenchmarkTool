#define _GNU_SOURCE
#include <mymutex.h>
#include <mythread.h>
#include <malloc.h>
#include <mythread_q.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * Function for initialization of the
 * mutex
 * */
int pthread_mymutex_init(pthread_mymutex_t *mutex, void *attr)
{
    mutex->state = INIT;
    return 0;
}

/**
 * Function for lock the other threads
 * */
int pthread_mymutex_lock(pthread_mymutex_t *mutex)
{
    if (mutex->state == INIT)
    {
        pid_t t = syscall(SYS_gettid);

        mutex->state = LOCK;
        mutex->tid = t;

        // pthread_private_t *thread;

        pthread_q_lock(t);
    }
    else
    {
        return -1;
    }

    return 0;
}

/**
 * Function for unlock all the other threads
 * */
int pthread_mymutex_unlock(pthread_mymutex_t *mutex)
{
    if (mutex->state == LOCK)
    {
        pid_t t = syscall(SYS_gettid);

        mutex->state = LOCK;
        mutex->tid = t;

        pthread_q_unlock(t);
    }
    else
    {
        return -1;
    }

    return 0;
}

int pthread_mymutex_trylock(pthread_mymutex_t *mutex)
{

    return 0;
}
