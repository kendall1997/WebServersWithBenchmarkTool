// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#include <stdio.h>
#include <time.h>

#include <scheduler_fifo.h>
#include <http.h>

/**
 * @brief      This algorithm handles the incoming request in a FIFO order
 *
 * @param[in]  slot      The slot
 * @param      requests  The requests
 */
void scheduler_fifo(int slot, struct Queue* requests){
  // We use the enqueue and dequeue operation just to 'follow the rule', but is not
  // actually necesary due to the operation is atomic

  // Put the request in the Queue Data Structure
  enqueue(requests, slot);

  // handle the HTTP request
  respond(slot);

  // Remove it from the queue
  dequeue(requests);

  // debug
  printf("Amount of requests: %d\n", getSize(requests));
  
}