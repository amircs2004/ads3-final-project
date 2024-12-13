#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Data type for stack and queue (representing data in stack / queue)
typedef int TypeElm;

// Book structure  ,, stores details for each book in the library
typedef struct {
    int bookID;   //the book identifier
    char title[50];  //the book title
    char author[50];  //the name of the author
    int isAvailable; // 1 = available, 0 = unavailable (availability status)
} Book;

// User structure for borrow request queue  (stores users detail for borrowing books )
typedef struct {
    int userID;  // identifier of the user
    char name[50]; //the name of the user
    int requestedBookID;  //the identifier of the requested book
} User;

// Declaration of Stack for Recently Returned Books
typedef struct Estack* Stack;  // Stack will hold Book data
typedef struct Estack {
    Book Data;  // Stack stores Book type data (recently returned books)
    Stack Next;    // Points to the next node in the stack
} SNode;

// Declaration of Queue for Borrow Requests
typedef struct Element* EQueue;// Queue will hold User data
typedef struct Element {
    User Data;    // Queue stores User type data (borrow request details)
    EQueue Next;    // Points to the next node in the queue
} QNode;
typedef struct {
    EQueue Head, Tail;  // Head and Tail pointers for the queue (FIFO structure)
} Queue;

// Stack Operations
void InitStack(Stack *P);       // Initialize an empty stack
void Push(Stack *S, Book x);      // Push a new Book to the stack (used for returned books)
void Pop(Stack *S, Book *x);       // Pop a Book from the stack (used when removing books from the recently returned list)
int isSEmpty(Stack S);          // Check if the stack is empty
Book Top(Stack S);           // Get the top book from the stack (used for browsing recently returned books)

// Queue Operations
void InitQueue(Queue *Q);    // Initialize an empty queue
void Enqueue(Queue *Q, User x);   // Enqueue a User to the borrow request queue (waiting for a book)
void Dequeue(Queue *Q, User *x);      // Dequeue a User from the borrow request queue (to process their borrow request)
int isQEmpty(Queue Q);         // Check if the queue is empty
User Head(Queue Q);           // Get the head of the queue (the first user waiting for a book)

// Library Operations
void AddBook(Book **inventory, int *count);       // Add a new Book to the library's inventory
void BorrowBook(Book *inventory, int count, Queue *requestQueue);     // Allow a User to borrow a Book, or add them to the request queue if unavailable
void ReturnBook(Book *inventory, int count, Stack *recentStack);      // Return a Book and add it to the recently returned stack
void ProcessRequests(Book *inventory, int count, Queue *requestQueue);    // Process any pending borrow requests when a book becomes available
void DisplayStack(Stack recentStack);    // Display the books in the recently returned stack
void DisplayQueue(Queue requestQueue);    // Display the users in the borrow request queue
void SearchBook(Book *inventory, int count);   // Search for a Book in the library's inventory






#endif // LIBRARY_H_INCLUDED
