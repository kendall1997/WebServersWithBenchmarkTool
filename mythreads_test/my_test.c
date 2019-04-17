#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "scheduler.h"
#include "my_thread.h"

/* Number of threads to start */
#define NTHREADS 8

void *threadFunction1()
{
    int i = 0;
    while (i != 20)
    {
        printf("THREAD 1 \n\n");
        i += 1;
    }
    my_thread_end();
    //mythread_exit(NULL);
    return NULL;
}

void *threadFunction2()
{
    int i = 0;
    while (i != 20)
    {

        printf("THREAD 2 \n\n");
        i += 1;
    }
    my_thread_end();
    //mythread_exit(NULL);
    return NULL;
}

void *threadFunction3()
{
    int i = 0;
    while (i != 20)
    {
        printf("THREAD 3 \n\n");
        i += 1;
    }

    my_thread_end();
    //mythread_exit(NULL);
    return NULL;
}

/* This is a simple demonstration of how to use the mythread library.
 */
int main()
{
    char *status;

    my_thread_create(&threadFunction1, NULL, 2, 3);
    my_thread_create(&threadFunction2, NULL, 10, 10);
    my_thread_create(&threadFunction3, NULL, 10, 10);

    my_thread_chsched("Sorteo");
    run_threads();

    return 0;
}
