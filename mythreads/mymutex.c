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
int mythread_mymutex_init(mythread_mymutex_t *mutex, void *attr)
{
    mutex->state = INIT;
    return 0;
}

/**
 * Function for lock the other threads
 * */
int mythread_mymutex_lock(mythread_mymutex_t *mutex)
{
    if (mutex->state == INIT)
    {
        pid_t t = syscall(SYS_gettid);

        mutex->state = LOCK;
        mutex->tid = t;

        // mythread_private_t *thread;

        mythread_q_lock(t);
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
int mythread_mymutex_unlock(mythread_mymutex_t *mutex)
{
    if (mutex->state == LOCK)
    {
        pid_t t = syscall(SYS_gettid);

        mutex->state = LOCK;
        mutex->tid = t;

        mythread_q_unlock(t);
    }
    else
    {
        return -1;
    }

    return 0;
}

int mythread_mymutex_trylock(mythread_mymutex_t *mutex)
{

    return 0;
}
