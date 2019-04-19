#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    while (i != 10)
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
    //mythread_mymutex_lock(&mutex);
    while (i != 10)
    {
        //setbuf(stdout, NULL);
        printf("THREAD 2 \n\n");
        sleep(1);
        i += 1;
    }
    sleep(1);
    //mythread_mymutex_unlock(&mutex);

    //mythread_exit(NULL);
    return NULL;
}

void *threadFunction3()
{
    int i = 0;
    while (i != 10)
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
int main(int argc, char **argv)
{
    mythread_t t1;
    mythread_t t2;
    mythread_t t3;

    // mythread_mymutex_init(&mutex, NULL);

    mythread_create(&t1, NULL, threadFunction1, NULL);
    mythread_create(&t2, NULL, threadFunction2, NULL);
    mythread_create(&t3, NULL, threadFunction3, NULL);

    mythread_sched(/*argv[1]*/ "LOTTERY");
    // mythread_join(t1, status);
    // mythread_join(t2, status);
    // mythread_join(t3, status);
    // mythread_detach(t1);
    // mythread_detach(t2);
    // mythread_detach(t3);

    // int array[3][5];

    // mythread_q_array_fill(&array, 3, 5);

    // mythread_q_print_array(&array, 3, 5);

    // while (1)
    // {
    //     printf("%d\n\n", rand() % 10);
    //     sleep(2);
    // }

    // int array[3] = {-1, -1, -1};

    // mythread_q_array_simple_append(array, 3, 4);

    // mythread_q_print_array_simple(array, 3);

    // printf("VERIFY %d\n", mythread_q_array_simple_verify(array, 3, 4));
    // printf("%d\n", mythread_q_array_simple_isfull(array, 3));

    // mythread_q_array_simple_append(array, 3, 5);

    // mythread_q_print_array_simple(array, 3);

    // printf("VERIFY %d\n", mythread_q_array_simple_verify(array, 3, 5));
    // printf("%d\n", mythread_q_array_simple_isfull(array, 3));

    // mythread_q_array_simple_append(array, 3, 0);

    // mythread_q_print_array_simple(array, 3);

    // printf("VERIFY %d\n", mythread_q_array_simple_verify(array, 3, 1));
    // printf("%d\n", mythread_q_array_simple_isfull(array, 3));

    return 0;
}
