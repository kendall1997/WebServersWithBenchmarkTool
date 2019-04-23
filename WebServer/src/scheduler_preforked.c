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
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>


#include <scheduler_preforked.h>
#include <http.h>

/**
 * @brief      This algorithm handles the incoming request in a parallel way (forked process)
 *
 * @param[in]  slot      The slot
 * @param      requests  The requests
 * @param      poolSize  Amount of request that can be handled at a time
 */
void scheduler_preforked(int slot, struct Queue* requests, int poolSize){

  // Set up for the webserver
  if(preforked_started == FALSE){

    // Lets share the memory
    preforked_poolConsume = mmap(NULL, sizeof *preforked_poolConsume, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0); // shared Memory between process
    
    // Initialize
    *preforked_poolConsume = 0;

    // Out flag
    preforked_started = TRUE;
    
  }

  *preforked_poolConsume = *preforked_poolConsume + 1;

  if(*preforked_poolConsume < (poolSize+1)){
    // lets create a child process
    int childProcessId = fork();

    // All code from here is running both in a parent and in a child process

    // Lets check who am I :)
    if( childProcessId == 0){ // I'm a child process

      // I'm running in a background process
      // Lets handle the HTTP request
      preforked_task(slot, requests);
      memset(preforked_poolConsume, *preforked_poolConsume-1, sizeof(preforked_poolConsume));

      // That's all I have to do
      // This process will finish gracefully
      // Code 0 means no error happened
      exit(0); 

      // No Zombie process from here

    }else{ // I'm a parent process

      // I have to do nothing here, just pass
      // to go listening for new incoming connections
      
    }
  }else{
    
    // There is not available workers here
    enqueue(requests, slot);

  }
  
}

/**
 * @brief      Task to be performed by the process
 *
 * @param[in]  slot  The slot
 */
void preforked_task(int slot, struct Queue* requests){

  // Execute the task
  respond(slot);
  
  // Analyze the pending
  if(getSize(requests) == 0){ // Enjoy free time, no task pending
    // noting to do
  }else{
    int new_slot = dequeue(requests);
    preforked_task(slot, requests);
    
  }
}