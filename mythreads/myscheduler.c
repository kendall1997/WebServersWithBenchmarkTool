#define _GNU_SOURCE
#include <myscheduler.h>
#include <mythread.h>
#include <malloc.h>
#include <mythread_q.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

#define FIFO_CHAR "FIFO"
#define SSROUNDROBIN_CHAR "SSROUNDROBIN"
#define LOTTERY_CHAR "LOTTERY"
#define REAL_CHAR "REAL"

int *scheduler_type;

/**
 * Function that receives the type of scheduler we
 * are going to realize
 * */

void mythread_sched(char *scheduler)
{

    if (!strcmp(scheduler, FIFO_CHAR))
    {
        scheduler_type = FIFO;
        mythread_fifo();
    }
    else if (!strcmp(scheduler, SSROUNDROBIN_CHAR))
    {
        scheduler_type = SSROUNDROBIN;
        mythread_ssroundrobin();
    }
    else if (!strcmp(scheduler, LOTTERY_CHAR))
    {
        scheduler_type = LOTTERY;
        mythread_lottery();
    }
    else if (!strcmp(scheduler, REAL_CHAR))
    {
        scheduler_type = REAL;
        mythread_real();
    }
    else
    {
        printf("ERROR, THIS SHCEDULER IS UNDEFINED \n\n");
    }
}

/**
 * Function for setup and realize the scheduler 
 * of fifo
 * */

void mythread_fifo()
{
    // mythread_q_lock_all();
    mythread_q_unlock_fifo();
}
/**
 * Function for setup and realize the scheduler 
 * of ssroundrobin
 * */

void mythread_ssroundrobin()
{
    // mythread_q_lock_all();
    mythread_q_ssrr();
}
/**
 * Function for setup and realize the scheduler 
 * of lottery
 * */

void mythread_lottery()
{

    // mythread_q_lock_all();
    mythread_q_lottery();
}

/**
 * Function for setup and realize the scheduler 
 * of realtime
 * */

void mythread_real()
{
    mythread_q_lock_all();
}
