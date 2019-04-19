#include <stdio.h>
#include <pthread.h>
#include "src/mythread.h"
#include <assert.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void *inc_x()
{

    int i = 0;

    while (i != 10)
    {
        printf("HOLA MUNDO\n");
        i++;
    }
}

int main(void)
{
    // int tstatus = 0;
    // int x = 0;
    // pthread_t inc_x_thread;

    /*if (pthread_create(&inc_x_thread, NULL, threadFunction, &x))
    {

        fprintf(stderr, "Error creating thread\n");
        return 1;
    }*/

    //mythread_t pid;

    //mythread_create(&pid, NULL, inc_x, NULL);

    int x = 0, y = 0;

    pid_t t1;

    /* show the initial values of x and y */
    printf("x: %d, y: %d\n", x, y);

    /* this variable is our reference to the second thread */
    pthread_t inc_x_thread;

    /* create a second thread which executes inc_x(&x) */
    if (pthread_create(&inc_x_thread, NULL, inc_x, NULL))
    {

        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    /* increment y to 100 in the first thread */
    // while (++y < 100);

    //printf("y increment finished\n");

    /* wait for the second thread to finish */
    if (pthread_join(inc_x_thread, NULL))
    {

        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    /* show the results - x is now 100 thanks to the second thread */
    // printf("x: %d, y: %d\n", x, y);

    return 0;
}
