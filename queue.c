#include "library.h"
// Initialize a queue
void InitQueue(Queue *Q) {
    Q->Head = NULL; // Set the Head pointer to NULL (queue is empty)
    Q->Tail = NULL;// Set the Tail pointer to NULL (queue is empty)
}

// Add a new user to the queue (Enqueue operation)
void Enqueue(Queue *Q, User x) {
    EQueue V = malloc(sizeof(QNode)); // Allocate memory for a new queue node
    V->Data = x;         // Assign the data (User) to the new node
    V->Next = NULL;      // Set the Next pointer of the new node to NULL
    if (Q->Head == NULL) {
        Q->Head = V;     // If empty, the new node becomes the Head
    } else {
        Q->Tail->Next = V;   // If not empty, link the new node to the current Tail
    }
    Q->Tail = V;       // Update the Tail to point to the new node
}

// Remove a user from the front of the queue (Dequeue operation)
void Dequeue(Queue *Q, User *x) {
    if (isQEmpty(*Q)) return;    // Check if the queue is empty; if so, return immediately
    EQueue V = Q->Head;   // Temporary pointer to store the current Head node
    *x = Q->Head->Data;      // Copy the data of the Head node to the output parameter (*x)
    if (Q->Head == Q->Tail) {  // If there is only one node in the queue
        Q->Head = NULL;
        Q->Tail = NULL;
             // (queue becomes empty)
    } else {
        Q->Head = Q->Head->Next;  // Move the Head pointer to the next node
    }
    free(V);  // Free the memory of the removed node
}

int isQEmpty(Queue Q) {
    return Q.Head == NULL;   // Return 1 (true) if Head is NULL, otherwise 0 (false)
}

User Head(Queue Q) {
    return Q.Head->Data;  // Return the data of the Head node
}
