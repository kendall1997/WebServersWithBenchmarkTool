#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ucontext.h>
#include "common.h"
#include "mythread.h"

#define MEM 8192
int thread_count = 1; //this counter is used to assign a unique ID to the threads when they are created.

_MyThread *current; //holds the current running thread.
Queue *ready;
Queue *blocked_queue;
ucontext_t initial_context; //saves the initial context to return to if there are no threads available to run.

void unblock(int i);
int activeChildren();

void MyThreadInit(void (*start_funct)(void *), void *args)
{
    ready = (Queue *)malloc(sizeof(Queue));
    blocked_queue = (Queue *)malloc(sizeof(Queue));
    initializeQueue(ready);
    initializeQueue(blocked_queue);
    _MyThread *Main = (_MyThread *)malloc(sizeof(_MyThread));
    getcontext(&(Main->cxt));
    Main->id = 1;
    Main->parent = NULL;
    Main->active = 1;
    Main->blocked = 0;
    Main->children = malloc(sizeof(Queue));
    (Main->children)->front = malloc(sizeof(QueueNode));
    (Main->children)->front = NULL;
    (Main->children)->rear = malloc(sizeof(QueueNode));
    (Main->children)->rear = NULL;
    Main->blocked_on = 0;
    (Main->cxt).uc_link = 0;
    (Main->cxt).uc_stack.ss_sp = malloc(MEM);
    (Main->cxt).uc_stack.ss_size = MEM;
    makecontext(&(Main->cxt), (void (*)())start_funct, 1, args);
    current = (_MyThread *)malloc(sizeof(_MyThread));
    current = Main;
    //printf("Before setting main context\n");
    swapcontext(&initial_context, &Main->cxt);
}
MyThread MyThreadCreate(void (*start_funct)(void *), void *args)
{
    _MyThread *MT = (_MyThread *)malloc(sizeof(_MyThread));
    //printf("Inside MyThread Create\n");
    MT->id = ++thread_count;
    MT->parent = current;
    MT->active = 1;
    MT->blocked = 0;
    MT->children = (Queue *)malloc(sizeof(Queue));
    initializeQueue(MT->children);
    MT->blocked_on = 0;
    getcontext(&(MT->cxt));
    (MT->cxt).uc_link = 0;
    (MT->cxt).uc_stack.ss_sp = malloc(MEM);
    (MT->cxt).uc_stack.ss_size = MEM;
    makecontext(&(MT->cxt), (void (*)())start_funct, 1, args);
    enQueue(current->children, MT);
    enQueue(ready, MT);
    //printf("New Thread created\n");
    return (void *)MT;
}
void MyThreadYield(void)
{
    int queue_size = size(ready);
    if (queue_size == 0)
        printf("Ready Queue is empty, No thread to yield to\n");
    else
    {

        _MyThread *running = current;
        enQueue(ready, current);
        if (size(ready) != 0)
        {
            current = deQueue(ready);
        }
        else
            current->cxt = initial_context;
        swapcontext(&(running->cxt), &(current->cxt));
    }
}

int MyThreadJoin(MyThread thread)
{
    int search_result = 0;
    _MyThread *internalThread = (_MyThread *)thread;
    if ((((_MyThread *)thread)->parent)->id == current->id)
        search_result = 1;

    //if the argument thread is not present in the children queue of current thread, return -1
    if (search_result == 0)
        return (-1);
    else
    { //If the child thread has already terminated, do nothing
        if (internalThread->active == 0)
        {
            printf("Child thread already terminated\n");
        }
        else
        {
            //If the child thread is active, block the current running thread
            if (((_MyThread *)thread)->active == 1)
            {
                (current)->blocked = 1;
                current->blocked_on = ((_MyThread *)thread)->id;
                enQueue(blocked_queue, current);
                if (size(ready) != 0)
                {
                    current = deQueue(ready);
                }
                else
                    current->cxt = initial_context;
                swapcontext(&((internalThread->parent)->cxt), &(current->cxt));
                //printf("After swapping\n");
            }
        }
    }
    return (1);
}

void MyThreadJoinAll(void)
{
    _MyThread *tempInJoinAll;
    int child_count = activeChildren();
    if (child_count > 0)
    {
        (current)->blocked = child_count;
        enQueue(blocked_queue, current);
        tempInJoinAll = current;
        if (size(ready) != 0)
        {
            current = deQueue(ready);
        }
        else
            current->cxt = initial_context;
        swapcontext(&(tempInJoinAll->cxt), &(current->cxt));
    }
}

int activeChildren()
{
    int active_children = 0;
    QueueNode *qnode = (QueueNode *)malloc(sizeof(QueueNode));
    qnode = (current->children)->front;
    while (qnode != NULL)
    {
        if (((qnode->queuenode_thread)->active) == 1)
            active_children++;
        qnode = qnode->next;
    }
    return (active_children);
}

void MyThreadExit(void)
{
    if (((current->blocked_on) == 0) && ((current->blocked) != 1))
    {
        //if current thread is not blocked, start termination process
        //Dereferencing the parent pointer of the terminating thread's children.
        _MyThread *terminating = (_MyThread *)malloc(sizeof(_MyThread));
        terminating = current;
        while (((terminating->children)->front) != NULL)
        {
            (((terminating->children)->front)->queuenode_thread)->parent = NULL;
            ((terminating->children)->front) = ((terminating->children)->front)->next;
        }
        //if parent of terminating thread exists.
        if ((current->parent) != NULL)
        {
            //if parent is waiting for terminating thread, unblock it and add to the ready queue.
            if (((current->parent)->blocked_on) != 0)
            {
                if ((((current->parent)->blocked_on)) == current->id)
                {
                    unblock((current->parent)->id);
                }
            }
            //if the parent has called JoinAll
            //each active parent on exiting will reduce the value of it's parent's blocked by one
            //until it becomes zero, when it unblocks the parent
            if ((((current->parent)->blocked_on) == 0) && (((current->parent)->blocked) > 0))
            {
                --((current->parent)->blocked);
                if (((current->parent)->blocked) == 0)
                {
                    unblock((current->parent)->id);
                }
            }
        }
        // set the first thread at the ready queue to be the new current thread.
        if (size(ready) != 0)
        {
            current = deQueue(ready);
        }
        else
            current->cxt = initial_context;
        terminating->active = 0;
        free(terminating->children);
        free((terminating->cxt).uc_stack.ss_sp);
        setcontext(&(current->cxt));
    }
    else
    {
        //this condition will not happen, because a blocked thread will not be able to call MyThreadExit.
        //this is for precaution and test purposes.
        printf("Blocked thread\n");
    }
}

void unblock(int i)
{

    //When a child calls unblock with its parent's id, the iterator looks for a thread with the same ID in the blocked queue,
    //adds it to the ready queue and removes it from the blocked queue.
    //deQueue function is not used because Blocked Queue is not a FIFO Queue.

    QueueNode *iterator = blocked_queue->front;
    if ((iterator->queuenode_thread)->id == i)
    {
        (iterator->queuenode_thread)->blocked = 0;
        (iterator->queuenode_thread)->blocked_on = 0;
        enQueue(ready, iterator->queuenode_thread);
        if (blocked_queue->front == blocked_queue->rear)
        {
            blocked_queue->front = NULL;
            blocked_queue->rear = NULL;
        }
        else
        {
            blocked_queue->front = (blocked_queue->front)->next;
        }
    }
    else
    {
        QueueNode *previous = blocked_queue->front;
        iterator = iterator->next;
        if (iterator != NULL)
        {
            while (iterator != NULL)
            {
                if ((iterator->queuenode_thread)->id == i)
                {
                    (iterator->queuenode_thread)->blocked = 0;
                    (iterator->queuenode_thread)->blocked_on = 0;
                    previous->next = iterator->next;
                    enQueue(ready, iterator->queuenode_thread);
                }
                iterator = iterator->next;
                previous = previous->next;
            }
        }
    }
}

MySemaphore MySemaphoreInit(int initialValue)
{
    _MySemaphore *mySemaphore = malloc(sizeof(_MySemaphore));
    if (initialValue < 0)
    {
        printf("Initial Value of Semaphore can not be negative\n");
    }
    else
    {
        mySemaphore->semaphore = initialValue;
        mySemaphore->semaphoreQ = malloc(sizeof(Queue));
        initializeQueue(mySemaphore->semaphoreQ);
        return (MySemaphore)mySemaphore;
    }
}
void MySemaphoreSignal(MySemaphore sem)
{
    _MySemaphore *mySem = (_MySemaphore *)sem;
    (mySem->semaphore) = (mySem->semaphore) + 1; //increase the semaphore by one.
    //if value of semaphore is greater than zero,
    //remove the first thread from the semaphore queue and add it to the ready queue.
    if ((mySem->semaphore) > 0)
    {
        if (size(mySem->semaphoreQ) != 0)
        {
            _MyThread *waitingThread = deQueue(mySem->semaphoreQ);
            enQueue(ready, waitingThread);
        }
    }
}

void MySemaphoreWait(MySemaphore sem)
{
    _MySemaphore *mySemWait = (_MySemaphore *)sem;
    (mySemWait->semaphore) = (mySemWait->semaphore) - 1; //decrease the semaphore by one.
    //if Semaphore is zero or less, add current thread to the semaphore queue.
    if ((mySemWait->semaphore) < 0)
    {
        _MyThread *waitThread = current;
        enQueue(mySemWait->semaphoreQ, waitThread);
        if (size(ready) != 0)
            current = deQueue(ready);
        else
            current->cxt = initial_context;
        swapcontext(&(waitThread->cxt), &(current->cxt));
    }
}
int MySemaphoreDestroy(MySemaphore sem)
{
    _MySemaphore *mySemDestroy = (_MySemaphore *)sem;
    int semQSize = size(mySemDestroy->semaphoreQ);
    if (semQSize == 0)
    {
        //if the Semaphore Queue is empty, destroy the semaphore
        free(mySemDestroy);
        return (0);
    }
    else
        return (-1);
}
//The following function was written for test purposes, to check the value of semaphores.
int SemaphoreValue(MySemaphore sem)
{
    _MySemaphore *mySemDestroy = (_MySemaphore *)sem;
    return (mySemDestroy->semaphore);
}
