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

#include <scheduler_fifo.h>
#include <http.h>

/**
 * @brief      This algorithm handles the incoming request in a parallel way (forked process)
 *
 * @param[in]  slot      The slot
 * @param      requests  The requests
 */
void scheduler_forked(int slot, struct Queue* requests){

  // lets create a child process
  int childProcessId = fork();

  // All code from here is running both in a parent and in a child process

  // Lets check who am I :)
  if( childProcessId == 0){ // I'm a child process

    // I'm running in a background process
    // Lets handle the HTTP request
    respond(slot);

    // That's all I have to do
    // This process will finish gracefully
    // Code 0 means no error happened
    exit(0); 

    // No Zombie process from here

  }else{ // I'm a parent process

    // I have to do nothing here, just pass
    // to go listening for new incoming connections
    
  }
  
}