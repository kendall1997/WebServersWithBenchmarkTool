// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#ifndef QUEUE_H
#define QUEUE_H
  
// A structure to represent a queue 
struct Queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    int* array; 
}; 
  
// function to create a queue of given capacity.  
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity);
  
// Queue is full when size becomes equal to the capacity  
int isFull(struct Queue* queue);
  
// Queue is empty when size is 0 
int isEmpty(struct Queue* queue);
  
// Function to add an item to the queue.   
// It changes rear and size 
void enqueue(struct Queue* queue, int item);
  
// Function to remove an item from queue.  
// It changes front and size 
int dequeue(struct Queue* queue);
  
// Function to get front of queue 
int front(struct Queue* queue);
  
// Function to get rear of queue 
int rear(struct Queue* queue);

// Function to get the size of the queue
int getSize(struct Queue* queue);

#endif