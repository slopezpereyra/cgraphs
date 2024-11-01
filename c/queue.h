#include <stdint.h>
#include <stdbool.h>
typedef uint32_t u32;

// A linked list (LL) node to store a queue entry
struct QNode {
    u32 key;
    struct QNode* next;
};
 
// The queue, front stores the front node of LL and rear
// stores the last node of LL
struct Queue {
    u32 count;
    struct QNode *front, *rear;
};
 
 
// A utility function to create a new linked list node.
struct QNode* newNode(u32 k);
 
// A utility function to create an empty queue
struct Queue* createQueue();
 
// The function to add a key k to q
void enQueue(struct Queue* q, u32 k);
 
// Function to remove a key from given queue q
void deQueue(struct Queue* q);

u32 pop(struct Queue* q);

bool isEmpty(struct Queue* q);

void dumpQueue(struct Queue* q);


int compareQueue(const void* a, const void* b);
int compareQueueDescending(const void* a, const void* b);

