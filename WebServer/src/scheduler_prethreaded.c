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
#include <pthread.h> 
#include <unistd.h>

#include <scheduler_prethreaded.h>
#include <queue.h>
#include <http.h>

/**
 * @brief      This algorithm handles the incoming request in a parallel way (forked process)
 *
 * @param[in]  slot      The slot
 * @param      requests  The requests
 */
void scheduler_prethreaded(int slot, struct Queue* requests, int poolSize){

  if(prethreaded_started == FALSE){

    // lets start initializing structures
    prethreaded_started = TRUE;
    prethreaded_working_count = 0;
    prethreaded_poolSize = poolSize;
    prethreaded_request = requests;

    // lets allocate the memory that will contain the slots
    prethreaded_slots = (int*) calloc(poolSize, sizeof(int));

    // lets create the thread pool structure
    threadPool = (pthread_t*) calloc(poolSize, sizeof(pthread_t));

    // Initialize the structures for each thread
    int threadCounter;
    for(threadCounter = 0; threadCounter < poolSize; ++threadCounter){
      // initialize the array for slots, if each value is -1, then no work assigned
      prethreaded_slots[threadCounter] = -1;

      // create the thread
      threadPool[threadCounter] = pthread_create (&threadPool[threadCounter], NULL, prethreaded_task, (void*) &threadCounter);

      // Let it run in the background
      pthread_detach(threadPool[threadCounter]);
    }
  }

  // Main logic that will run on each request

  // Is there any worker available?
  if(prethreaded_working_count < poolSize){ // yeap there is
    

    // lets find it
    int threadCounter;
    for(threadCounter = 0; threadCounter < prethreaded_poolSize; ++threadCounter){
      
      if(prethreaded_slots[threadCounter] == -1){ // -1 means available

        // store the slot in the shared memory
        // in the background, the selected thread
        // will be waiting for values different to
        // -1 to start serving the client's request
        prethreaded_slots[threadCounter] = slot;

        // already finded
        // there is not need to keep iterating for 
        // other threads
        break; 
      } 
    }

    // Increase the threads counter due to there is another
    // busy thread
    prethreaded_working_count++;

  }else{ // Nope, there is not

    printf("No space\n");
    // add it to the queue
    enqueue(requests, slot);

    // continue, not blocking the main thread for accept
    // new connections
  }
  
}

/**
 * @brief      This method allow us run the respond method from the http library
 *
 * @param      package  The package, contains the slot id
 *
 * @return     a void* pointer, is useful only when a function return pthread_exit is executed
 */
void* prethreaded_task(void* package){

  // Desreference a cast to integer to get the thread id
  int threadId =  *(( int* ) package);

  while(TRUE) {
    // check if there is work to do
    int slot = prethreaded_slots[threadId];
    if (slot >= 0){ // there is available work to do :)

      // response the http request
      prethreaded_work(slot);

      // handle post work job
      prethreaded_after_work(threadId);

    }else{
      //printf("No work on thread %d\n", threadId);
    }

    int checkTimeDelay = 100;

    usleep(checkTimeDelay*1000); // ms
  }

  
  

  // Return so the tread will exit
  return NULL;
}

/**
 * @brief      This function handles the thread's main job
 *
 * @param[in]  slot  The slot
 */
void prethreaded_work(int slot){
  respond(slot);
  printf("Out of thread\n");
}


/**
 * @brief      This method will restart the slot used in the thread,
 *             allowing the worker to be available
 *
 * @param[in]  threadId  The thread identifier
 */
void prethreaded_after_work(int threadId){

  // start atomic transaction
  pthread_mutex_lock(&lockWrite); 
  
  // check if there is more work to do
  if(getSize(prethreaded_request) == 0){ // Enjoy free time ;)
    // make the slot available again
    prethreaded_slots[threadId] = -1;

    // reduce the amount of current busy workers
    prethreaded_working_count--;
  }else{ // There is work to do

    // get from the queue the new slot
    int new_slot = dequeue(prethreaded_request);
    
    // update the slot, so, in the next
    // iteration the thread will use this
    // channel
    prethreaded_slots[threadId] = new_slot;

    // there is not need to update the working
    // count variable
    // thread is still busy
    // Code should be the following, but is not necessary
    // prethreaded_working_count = prethreaded_working_count;
  }

  // end atomic transaction
  pthread_mutex_unlock(&lockWrite); 
}