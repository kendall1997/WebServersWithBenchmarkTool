#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mythread.h>
#include <mythread_q.h>
#include <unistd.h>
#include <mymutex.h>
#include <sys/syscall.h>
#include <sys/types.h>

/* Number of threads to start */
#define NTHREADS 8

pthread_mymutex_t mutex;

void *threadFunction1()
{
    int i = 0;
    while (i != 50000)
    {
        //setbuf(stdout, NULL);
        printf("THREAD 1 \n\n");
        sleep(0.5);
        i += 1;
    }
    sleep(1);
    pthread_exit(NULL);
    return NULL;
}

void *threadFunction2()
{
    int i = 0;
    //pthread_mymutex_lock(&mutex);
    while (i != 50000)
    {
        //setbuf(stdout, NULL);
        printf("THREAD 2 \n\n");
        sleep(0.5);
        i += 1;
    }
    //sleep(1);
    //pthread_mymutex_unlock(&mutex);

    pthread_exit(NULL);
    return NULL;
}

void *threadFunction3()
{
    int i = 0;
    while (i != 50000)
    {
        //setbuf(stdout, NULL);
        printf("THREAD 3 \n\n");
        sleep(0.5);
        i += 1;
    }
    sleep(1);

    pthread_exit(NULL);
    return NULL;
}

void *threadFunction(void *ptr)
{

    int value = (int *)ptr;

    int i = 0;
    //printf("HELLO");
    while (i != 100)
    {
        //setbuf(stdout, NULL);
        printf("THREAD %d \n\n", value);
        sleep(0.5);
        i += 1;
    }
    //sleep(1);

    // printf("%d \n", t);
    pthread_exit(NULL);
    return NULL;
}
/* This is a simple demonstration of how to use the mythread library.
 */
int main(int argc, char **argv)
{

    int x[3] = {0, 1, 2};
    pthread_t array[4], t1;

    char *str = "HelloWorld";

    // pthread_create(&array, NULL, threadFunction, x[0]);
    // pthread_join(array, NULL);
    // pthread_create(&array[3], NULL, threadFunction, x[2] + 1);

    // int i;
    // for (i = 0; i < 3; ++i)
    // {
    //     sleep(1);
    //     pthread_create(&array[i], NULL, threadFunction, x[i]);
    // }

    // for (int j = 0; j < 3; ++j)
    // {
    //     pthread_detach(array[j]);
    //     sleep(1);
    // }

    pthread_create(&t1, NULL, threadFunction, x[0]);
    //printf("thread: %ld\n", (unsigned long)t1);
    pthread_detach(t1);
    //pthread_join(t1, NULL);

    // pthread_sched(/*argv[1]*/ "LOTTERY");

    // for (int j = 0; j < 3; ++j)
    // {
    //     pthread_detach(array[j]);
    //     sleep(1);
    // }

    // pthread_t t1;
    // pthread_t t2;
    // pthread_t t3;

    // pthread_mymutex_init(&mutex, NULL);

    // pthread_create(&t1, NULL, threadFunction1, NULL);
    // pthread_create(&t2, NULL, threadFunction2, NULL);
    // pthread_create(&t3, NULL, threadFunction3, NULL);

    // pthread_sched(/*argv[1]*/ "SSROUNDROBIN");
    // pthread_join(t1, status);
    // pthread_join(t2, status);
    // pthread_join(t3, status);
    // pthread_detach(t1);
    // pthread_detach(t2);
    // pthread_detach(t3);

    // int array[3][5];

    // pthread_q_array_fill(&array, 3, 5);

    // pthread_q_print_array(&array, 3, 5);

    // while (1)
    // {
    //     printf("%d\n\n", rand() % 10);
    //     sleep(2);
    // }

    // int array[3] = {-1, -1, -1};

    // pthread_q_array_simple_append(array, 3, 4);

    // pthread_q_print_array_simple(array, 3);

    // printf("VERIFY %d\n", pthread_q_array_simple_verify(array, 3, 4));
    // printf("%d\n", pthread_q_array_simple_isfull(array, 3));

    // pthread_q_array_simple_append(array, 3, 5);

    // pthread_q_print_array_simple(array, 3);

    // printf("VERIFY %d\n", pthread_q_array_simple_verify(array, 3, 5));
    // printf("%d\n", pthread_q_array_simple_isfull(array, 3));

    // pthread_q_array_simple_append(array, 3, 0);

    // pthread_q_print_array_simple(array, 3);

    // printf("VERIFY %d\n", pthread_q_array_simple_verify(array, 3, 1));
    // printf("%d\n", pthread_q_array_simple_isfull(array, 3));

    // int array[3] = {4, 2, 8};

    // pthread_q_swap_rr(array, 3);

    //pthread_q_print_array_simple(array, 3);

    return 0;
}
