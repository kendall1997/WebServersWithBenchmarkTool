// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#include <middleware.h>

#include <stdio.h>
#include <string.h>

#include <http.h>
#include <config.h>
#include <log4us.h>

#include <scheduler_fifo.h>
#include <scheduler_forked.h>
#include <scheduler_threaded.h>
#include <scheduler_prethreaded.h>
#include <scheduler_preforked.h>

void startScheduler(struct config inheritedEnvironment){
  // Storing environment
  environment = inheritedEnvironment;

  // creque initializing
  log4us("Created request's queue");
  requests = createQueue(MAX_REQUESTS);
  
  // Save to log the scheduling algorithm to use
  log4us("Scheduling algorithm selected: ");
  log4us(inheritedEnvironment.scheduler);

  // Set pool value
  log4us("Pool value: ");
  char poolValue[255];
  sprintf(poolValue,"%d",environment.pool);
  log4us(poolValue);
  
  // start the webserver
  log4us("HTTP Server started");
  startHTTP(inheritedEnvironment.port, inheritedEnvironment.folder);
  
}


/**
 * @brief      This is a main scheduler functions, detects which is the selected scheduling algorithm
 *
 * @param[in]  slot  The slot
 */
void scheduler(int slot){
  
  constant SCHEDULER = environment.scheduler;

  if(strcmp(SCHEDULER,"FIFO") == 0){ // Handler for FIFO algorithm

    scheduler_fifo(slot, requests);

  }else if(strcmp(SCHEDULER,"FORKED") == 0){ // Handler for FORKED algorithm

    scheduler_forked(slot, requests);

  }else if(strcmp(SCHEDULER,"THREADED") == 0){ // Handler for THREADED algorithm

    scheduler_threaded(slot, requests);

  }else if(strcmp(SCHEDULER,"PRETHREADED") == 0){ // Handler for PRETHREADED algorithm

    scheduler_prethreaded(slot, requests, environment.pool);

  }else if(strcmp(SCHEDULER,"PREFORKED") == 0){ // Handler for PREFORKED algorithm
    
    scheduler_preforked(slot, requests, environment.pool);

  }else{ // Default is going to be FIFO

    scheduler_fifo(slot, requests);

  }

}