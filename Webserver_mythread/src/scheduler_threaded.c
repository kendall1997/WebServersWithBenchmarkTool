// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
// #include <pthread.h>
#include <../../mythreads/mythread.h>
#include <../../mythreads/mymutex.h>
#include <scheduler_threaded.h>
#include <http.h>

/**
 * @brief      This algorithm handles the incoming request in a parallel way (threads)
 *
 * @param[in]  slot      The slot
 * @param      requests  The requests
 */
void scheduler_threaded(int slot, struct Queue *requests)
{

    // Threads counter, will be useful for Pre-Threaded implementation
    int tstatus = 0, count = 0;

    // Thread identifier;
    mythread_t tid;

    // Create a thread saving if the creation was successful
    tstatus = mythread_create(&tid, NULL, backgroundTask, (void *)&slot);

    // Let it work in the background
    mythread_detach(tid);

    // Increase the threads counter
    count++;
}

/**
 * @brief      This method allow us run the respond method from the http library
 *
 * @param      package  The package, contains the slot id
 *
 * @return     a void* pointer, is useful only when a function return pthread_exit is executed
 */
void *backgroundTask(void *package)
{

    // Desreference a cast to integer the slot
    int slot = *((int *)package);

    // Execute the http respond task
    respond(slot);

    // Return so the tread will exit
    return NULL;
}
