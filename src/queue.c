#include "queue.h"
#include <stdbool.h>
// A C program to demonstrate linked list based
// implementation of queue
//

// A utility function to create a new linked list node.
struct QNode* newNode(u32 k)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    if (temp == NULL){
        printf("Error: malloc failed\n");
        exit(1);
    }
    temp->key = k;
    temp->next = NULL;
    return temp;
}


// A utility function to create an empty queue
struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    if (q == NULL){
        printf("Error: malloc failed\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    q -> count = 0;
    return q;
}
 
// The function to add a key k to q
void enQueue(struct Queue* q, u32 k)
{
    // Create a new LL node
    struct QNode* temp = newNode(k);
    ( q -> count )++;

    // If queue is empty, then new node is front and rear
    // both
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
 
    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}
 
// Function to remove a key from given queue q
void deQueue(struct Queue* q)
{
    ( q -> count )--;
    // If queue is empty, return NULL.
    if (q->front == NULL)
        return;
    // Store previous front and move front one node ahead
    struct QNode* temp = q->front;
 
    q->front = q->front->next;
 
    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;
 
    free(temp);
}

u32 pop(struct Queue* q){
    u32 front = q -> front -> key;
    deQueue(q);
    return(front);
}

bool isEmpty(struct Queue* q){
    return(q -> front == NULL);
}

void dumpQueue(struct Queue* q){
    while (q -> front != NULL){
        deQueue(q);
    }
    free(q);
}

int compareQueue(const void* a, const void* b) {
    struct Queue** queueA = (struct Queue**)a;
    struct Queue** queueB = (struct Queue**)b;

    return ((*queueA)->count - (*queueB)->count );
}

int compareQueueDescending(const void* a, const void* b) {
    struct Queue** queueA = (struct Queue**)a;
    struct Queue** queueB = (struct Queue**)b;

    return ((*queueB)->count - (*queueA)->count );
}
