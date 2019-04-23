// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#ifndef SCHEDULER_PRETHREADED
#define SCHEDULER_PRETHREADED

#define FALSE 0
#define TRUE 1

#include <queue.h>
// #include <pthread.h>
#include <../../mythreads/mythread.h>
#include <../../mythreads/mymutex.h>

static struct Queue *prethreaded_request;
static mythread_t *threadPool;
static int prethreaded_started = FALSE;
static int prethreaded_working_count;
static int *prethreaded_slots;
static int prethreaded_poolSize;
static mythread_mymutex_t lockWrite;
static mythread_mymutex_t lockRead;

void scheduler_prethreaded(int slot, struct Queue *requests, int poolSize);
void *prethreaded_task(void *package);
void prethreaded_work(int slot);
void prethreaded_after_work(int threadId);

#endif
