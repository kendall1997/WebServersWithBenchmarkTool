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

void mythread_fifo()
{
    mythread_q_lock_all();
    mythread_q_unlock_fifo();
}

void mythread_ssroundrobin()
{
    mythread_q_lock_all();
}

void mythread_lottery()
{

    mythread_q_lock_all();
    int number_threads = mythread_q_count();
    int array[number_threads][5];

    int number_max = number_threads * 5;

    int full = 0;

    int rand_number;

    mythread_q_array_fill(array, 3, 5);
    //mythread_q_print_array(array, number_threads, 5);

    while (full != 1)
    {
        rand_number = rand() % ((number_threads * 5));
        //printf("RANDOM: %d\n", rand_number);
        if (!mythread_q_array_verify(array, number_threads, 5, rand_number))
        {

            mythread_q_array_append(array, number_threads, 5, rand_number);
            //mythread_q_print_array(array, number_threads, 5);
        }
        full = mythread_q_array_isfull(array, number_threads, 5);
    }
    //mythread_q_print_array(array, number_threads, 5);
    int tickets[number_threads];
    mythread_q_choose_tickets(array, number_threads, 5, tickets);

    mythread_q_unlock_lottery(tickets, number_threads);
}

void mythread_real()
{
    mythread_q_lock_all();
}
