#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/* Number of threads to start */
#define NTHREADS 8

void *threadFunction1()
{
    int i = 0;
    while (i != 100)
    {
        //setbuf(stdout, NULL);
        printf("THREAD 1 \n\n");
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
    while (i != 100)
    {
        //setbuf(stdout, NULL);
        printf("THREAD 2 \n\n");
        sleep(1);
        i += 1;
    }
    sleep(1);
    //mythread_exit(NULL);
    return NULL;
}

void *threadFunction3()
{
    int i = 0;
    while (i != 100)
    {
        //setbuf(stdout, NULL);
        printf("THREAD 3 \n\n");
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
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, threadFunction1, NULL);
    pthread_create(&t2, NULL, threadFunction2, NULL);
    pthread_create(&t3, NULL, threadFunction3, NULL);
    // pthread_join(t1, NULL);
    // pthread_join(t2, NULL);
    // pthread_join(t3, NULL);
    pthread_detach(t1);
    pthread_detach(t2);
    pthread_detach(t3);

    return 0;
}
