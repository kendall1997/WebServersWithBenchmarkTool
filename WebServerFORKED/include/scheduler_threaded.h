// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#ifndef SCHEDULER_THREADED
#define SCHEDULER_THREADED

#define MAX_THREADS

#include <queue.h>

void scheduler_threaded(int slot, struct Queue* requests);
void* backgroundTask(void* package);

#endif
