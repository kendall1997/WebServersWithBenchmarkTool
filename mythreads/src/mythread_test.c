#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <mythread.h>
#include <mythread_q.h>
#include <unistd.h>
#include <mymutex.h>

/* Number of threads to start */
#define NTHREADS 8

mythread_mymutex_t mutex;

void *threadFunction1()
{
    int i = 0;
    while (i != 20)
    {
        //setbuf(stdout, NULL);
        //printf("THREAD 1 \n\n");
        sleep(1);
        i += 1;
    }
    sleep(1);
    //mythread_exit(NULL);
    return NULL;
}

void *threadFunction2()
{
    int i = 0;
    mythread_mymutex_lock(&mutex);
    while (i != 20)
    {
        //setbuf(stdout, NULL);
        //printf("THREAD 2 \n\n");
        sleep(1);
        i += 1;
    }
    sleep(1);
    mythread_mymutex_unlock(&mutex);

    //mythread_exit(NULL);
    return NULL;
}

void *threadFunction3()
{
    int i = 0;
    while (i != 20)
    {
        //setbuf(stdout, NULL);
        //printf("THREAD 3 \n\n");
        sleep(1);
        i += 1;
    }
    sleep(1);

    //mythread_exit(NULL);
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

    mythread_mymutex_init(&mutex, NULL);

    mythread_create(&t1, NULL, threadFunction1, NULL);
    mythread_create(&t2, NULL, threadFunction2, NULL);
    mythread_create(&t3, NULL, threadFunction3, NULL);
    mythread_join(t1, status);
    mythread_join(t2, status);
    mythread_join(t3, status);
    // mythread_detach(t1);
    // mythread_detach(t2);
    // mythread_detach(t3);

    return 0;
}
