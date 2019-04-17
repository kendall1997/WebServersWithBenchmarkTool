#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <mythread.h>

/* Number of threads to start */
#define NTHREADS 8

void *threadFunction1()
{
    int i = 0;
    while (i != 100)
    {
        printf("THREAD 1 \n");
        i += 1;
    }

    mythread_exit(NULL);
    return NULL;
}

void *threadFunction2()
{
    int i = 0;
    while (i != 100)
    {
        printf("THREAD 2 \n");
        i += 1;
    }

    mythread_exit(NULL);
    return NULL;
}

void *threadFunction3()
{
    int i = 0;
    while (i != 100)
    {
        printf("THREAD 3 \n");
        i += 1;
    }

    mythread_exit(NULL);
    return NULL;
}

/* This is a simple demonstration of how to use the mythread library.
 */
int main()
{
    char *status;
    mythread_t t1;
    mythread_t t2;
    mythread_t t3;

    mythread_create(&t1, NULL, threadFunction1, NULL);
    mythread_create(&t2, NULL, threadFunction2, NULL);
    mythread_create(&t3, NULL, threadFunction3, NULL);
    mythread_detach(t1);
    mythread_detach(t2);
    mythread_detach(t3);

    return 0;
}
