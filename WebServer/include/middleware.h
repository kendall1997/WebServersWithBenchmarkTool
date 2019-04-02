// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#define MAX_REQUESTS 1000000

#include <queue.h>
#include <config.h>

typedef const char* constant;


struct Queue* requests;
static struct config environment;

void startScheduler();

void scheduler(int slot);





#endif
