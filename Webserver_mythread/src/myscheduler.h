#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mythread.h>
#include <sched.h>

#ifndef MYSCHEDULER_H
#define MYSCHEDULER_H

#define FALSE 0
#define TRUE 1

void mythread_sched(char *scheduler);

#endif
