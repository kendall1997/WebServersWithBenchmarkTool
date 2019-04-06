// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#include <agent.h>

// Auxiliar states

static int total_runs;
static int total_cycles;
static int current_runs;
static char* url_requested;
static struct summary* results;





void work(char* url, int threads, int cycles);
void* task(void* args);

int main(int argc, char const *argv[]){
  char* host = argv[1];
  char* port = argv[2];
  char* file = argv[3];
  char* threads_str = argv[4];
  char* cycles_str = argv[5];

  int threads = atoi(threads_str);
  int cycles = atoi(cycles_str);

  char url[300];
  sprintf(url, "http://%s:%s/%s", host, port, file);


  printf("Remote resource to be downloaded for benchmarking, %s\n", url);

  printf("Run, Iteration, DateTimeStart, DateTimeEnd, Time Elapsed, File Size, File Name, Type of File\n");


  work(url, threads, cycles);

  //getchar();

  return 0;
}

void work (char* url, int threads, int cycles){
  total_runs = threads * cycles;
  current_runs = 0;
  total_cycles = cycles;
  url_requested = url;

  size_t allocated_results_space = sizeof(struct summary) * total_runs;
  results = calloc(total_runs, sizeof(struct summary));

  
  pthread_t thread[threads];

  int thread_counter;
  for(thread_counter = 0; thread_counter < threads; ++thread_counter){
    pthread_create( &thread[thread_counter], NULL, task, (void*) url );
  }

  int thread_join_counter;
  for(thread_join_counter = 0; thread_join_counter < threads; ++thread_join_counter){
    //printf("Waiting for %d\n", thread_join_counter);
    pthread_join( &thread[thread_join_counter],NULL );
  }

  printf("Acá ####\n");

  int task_count;
  for(task_count = 0; task_count < total_runs; ++task_count){
    struct summary* run = &results[task_count];

   
  }



}


void* task(void* args){
  pthread_mutex_t lock;

  char* url = (char*) args;
  int iteration;
  for(iteration = 0; iteration < total_cycles; ++iteration){
    // Main job
    struct summary* run = pull(url_requested);

    char tmp1[50];
    char tmp2[50];

    sprintf(tmp1, "%s", asctime(localtime(&run->DateStart)));
    sprintf(tmp2, "%s", asctime(localtime(&run->DateEnd)));

    tmp1[strlen(tmp1)-1] = 0;
    tmp2[strlen(tmp2)-1] = 0;

    printf("%d, %d, %s, %s, %d, %.0f, %s, %s\n", current_runs, iteration, tmp1, tmp2, run->ResponseTime, run->size, run->name, run->TypeOfFile);

    // Lock for store result
    pthread_mutex_lock(&lock);

    results[current_runs] = *run;

    current_runs++;

    pthread_mutex_unlock(&lock);
    
  }

  if(current_runs == total_runs){
    exit(EXIT_SUCCESS);
  }

  pthread_exit(NULL);
}