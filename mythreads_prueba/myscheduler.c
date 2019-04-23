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

void pthread_sched(char *scheduler)
{

    if (!strcmp(scheduler, FIFO_CHAR))
    {
        scheduler_type = FIFO;
        pthread_fifo();
    }
    else if (!strcmp(scheduler, SSROUNDROBIN_CHAR))
    {
        scheduler_type = SSROUNDROBIN;
        pthread_ssroundrobin();
    }
    else if (!strcmp(scheduler, LOTTERY_CHAR))
    {
        scheduler_type = LOTTERY;
        pthread_lottery();
    }
    else if (!strcmp(scheduler, REAL_CHAR))
    {
        scheduler_type = REAL;
        pthread_real();
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

void pthread_fifo()
{
    // pthread_q_lock_all();
    pthread_q_unlock_fifo();
}
/**
 * Function for setup and realize the scheduler 
 * of ssroundrobin
 * */

void pthread_ssroundrobin()
{
    // pthread_q_lock_all();
    pthread_q_ssrr();
}
/**
 * Function for setup and realize the scheduler 
 * of lottery
 * */

void pthread_lottery()
{

    // pthread_q_lock_all();
    pthread_q_lottery();
}

/**
 * Function for setup and realize the scheduler 
 * of realtime
 * */

void pthread_real()
{
    pthread_q_unlock_fifo();
}
