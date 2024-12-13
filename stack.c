#include "library.h"
   // Initialize the stack
void InitStack(Stack *P) {
    *P = NULL;         // Set the stack pointer to NULL, indicating an empty stack
}
// Push a book onto the stack (Add a book to the top of the stack)
void Push(Stack *S, Book x) {
    Stack V = malloc(sizeof(SNode));     // Allocate memory for a new node (SNode)
    V->Data = x;       // Assign the book data to the new node
    V->Next = *S;      // Link the new node to the current top of the stack
    *S = V;             // Update the top of the stack to point to the new node
}

// Pop a book from the stack (Remove the top book and retrieve its data)
void Pop(Stack *S, Book *x) {
    Stack V = *S;        // Temporary pointer to hold the current top node
    *x = (*S)->Data;     // Copy the data from the top node into the output parameter (*x)
    *S = (*S)->Next;        // Move the stack pointer to the next node in the stack
    free(V);      // Free the memory of the removed node

}

int isSEmpty(Stack S) {
    return S == NULL;      // Return 1 (true) if the stack pointer is NULL, otherwise 0 (false)
}

// Get the book at the top of the stack without removing it
Book Top(Stack S) {
    return S->Data;     // Return the data (book) from the top node of the stack
}


