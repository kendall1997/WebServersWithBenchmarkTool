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

#include <scheduler_threaded.h>
#include <http.h>

/**
 * @brief      This algorithm handles the incoming request in a parallel way (forked process)
 *
 * @param[in]  slot      The slot
 * @param      requests  The requests
 */
void scheduler_threaded(int slot, struct Queue* requests){

  int err = 0, count = 0; 
  pthread_t tid; 

  err = pthread_create (&tid, NULL, backgroundTask, (void*) &slot); 
  pthread_detach(tid);
  count++; 

  printf("Acá\n");
  
}

void* backgroundTask(void* package){
  int slot =  *(( int* ) package);
  printf("Slot %d\n", slot);
  respond(slot);
  return NULL;
}