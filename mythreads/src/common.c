#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ucontext.h>

#include "common.h"

void initializeQueue(Queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
    //printf("initialized\n");
}

int size(Queue *queue)
{
    int i = 0;
    QueueNode *temp;
    temp = queue->front;
    while (temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return (i);
}

void enQueue(Queue *q, _MyThread *th)
{
    QueueNode *qn = malloc(sizeof(QueueNode));
    qn->queuenode_thread = th;
    qn->next = NULL;
    if (size(q) == 0)
    {
        q->front = qn;
        q->rear = qn;
    }
    else
    {
        (q->rear)->next = qn;
        (q->rear) = (q->rear)->next;
    }
}

_MyThread *deQueue(Queue *q)
{
    if (size(q) == 0)
    {
        return (NULL);
    }
    else
    {
        _MyThread *mt = malloc(sizeof(_MyThread));
        if ((q->front) == (q->rear))
        {
            mt = (q->front)->queuenode_thread;
            q->front = NULL;
            q->rear = NULL;
        }
        else
        {
            mt = (q->front)->queuenode_thread;
            q->front = (q->front)->next;
        }
        return (mt);
    }
}
