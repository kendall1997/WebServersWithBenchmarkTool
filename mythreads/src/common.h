#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ucontext.h>

typedef struct Queue Queue;

typedef struct InternalMyThread
{
    ucontext_t cxt;
    struct InternalMyThread *parent;
    struct Queue *children;
    int blocked_on;
    int active;
    int blocked;
    int id;
} _MyThread;

typedef struct QueueNode
{
    struct InternalMyThread *queuenode_thread;
    struct QueueNode *next;
} QueueNode;

struct Queue
{
    QueueNode *front;
    QueueNode *rear;
};

typedef struct InternalMySemaphore
{
    int semaphore;
    Queue *semaphoreQ;
} _MySemaphore;

void initializeQueue(Queue *queue);

int size(Queue *queue);

void enQueue(Queue *q, _MyThread *th);

_MyThread *deQueue(Queue *q);
