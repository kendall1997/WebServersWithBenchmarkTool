// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#ifndef SCHEDULER_PREFORKED
#define SCHEDULER_PREFORKED

#define FALSE 0
#define TRUE 1

#include <queue.h>

static int preforked_started = FALSE;
int *preforked_poolConsume;

void scheduler_preforked(int slot, struct Queue *requests, int poolSize);
void preforked_task(int slot, struct Queue *requests);

#endif
