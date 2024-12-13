#include "library.h"

// Function to Initialize Books and Users
void InitializeLibrary(Book **inventory, int *count, Stack *recentStack, Queue *requestQueue) {
    // Initialize Books in Inventory
    *count = 3;
    *inventory = malloc((*count) * sizeof(Book));

    (*inventory)[0] = (Book){1, "analyse", "got", 1};
    (*inventory)[1] = (Book){2, "baby gavi", "ekly", 1};
    (*inventory)[2] = (Book){3, "Tokill", "paku", 0}; // Already borrowed

    // Add some books to Recently Returned Stack
    Push(recentStack, (Book){4, "algo", "besaa", 1});
    Push(recentStack, (Book){5, "archi", "mekhaldi", 1});

    // Add some Users to Borrow Request Queue
    Enqueue(requestQueue, (User){101, "ahmed", 3}); // Waiting for "To Kill "
    Enqueue(requestQueue, (User){102, "akram", 2});   // Waiting for "baby gavi"
}

// Function to add a new book to the inventory
void AddBook(Book **inventory, int *count) {

    // Increase the size of the inventory dynamically
    (*inventory) = realloc((*inventory), (*count + 1) * sizeof(Book));

    // Accept details of the new book from the user
    printf("Enter Book ID: ");
    scanf("%d", &((*inventory)[*count].bookID));
    printf("Enter Book Title: ");
    scanf(" %[^\n]", (*inventory)[*count].title);
    printf("Enter Author: ");
    scanf(" %[^\n]", (*inventory)[*count].author);

    // Mark the new book as available
    (*inventory)[*count].isAvailable = 1;
    // Increment the book count
    (*count)++;
    printf("Book Added Successfully!\n");
}


// Function to allow a user to borrow a book
void BorrowBook(Book *inventory, int count, Queue *requestQueue) {
    int bookID, userID;
    char userName[50];

    // Accept user details and the requested book ID
    printf("Enter User ID: ");
    scanf("%d", &userID);
    printf("Enter User Name: ");
    scanf(" %[^\n]", userName);
    printf("Enter Book ID to Borrow: ");
    scanf("%d", &bookID);

// Check if the requested book exists in the inventory
    for (int i = 0; i < count; i++) {
        if (inventory[i].bookID == bookID) {
            if (inventory[i].isAvailable) {
                inventory[i].isAvailable = 0;
                // If the book is available, mark it as borrowed
                printf("Book Borrowed Successfully!\n");
                return;
            } else {
                // If the book is unavailable, add the user to the borrow request queue
                User newUser = {userID, "", bookID};
                strcpy(newUser.name, userName);
                Enqueue(requestQueue, newUser);
                printf("Book is unavailable. Added to borrow request queue.\n");
                return;
            }
        }
    }
    printf("Book Not Found!\n");
}
// Function to return a book and add it to the recently returned stack
void ReturnBook(Book *inventory, int count, Stack *recentStack) {
    int bookID;
    printf("Enter Book ID to Return: ");
    scanf("%d", &bookID);
    // Search for the book in the inventory
    for (int i = 0; i < count; i++) {
        if (inventory[i].bookID == bookID) {
                  // Mark the book as available and add it to the stack
            inventory[i].isAvailable = 1;
            Push(recentStack, inventory[i]);
            printf("Book Returned Successfully!\n");
            return;
        }
    }
    printf("Book Not Found!\n");
}
// Function to process the next borrow request in the queue
void ProcessRequests(Book *inventory, int count, Queue *requestQueue) {
    if (isQEmpty(*requestQueue)) {
        printf("No pending borrow requests.\n");
        return;
    }
       // Get the next user from the queue
    User user;
    Dequeue(requestQueue, &user);

        // Search for the requested book in the inventory
    for (int i = 0; i < count; i++) {
        if (inventory[i].bookID == user.requestedBookID) {
            if (inventory[i].isAvailable) {
                // if the book is available ,, mark it as borrowed
                inventory[i].isAvailable = 0;
                printf("Request Processed: User %s has borrowed '%s'\n", user.name, inventory[i].title);
            } else {
                printf("Book '%s' is still unavailable.\n", inventory[i].title);
            }
            return;
        }
    }
    printf("Requested Book Not Found!\n");
}

// Function to display the borrow request queue
void DisplayStack(Stack recentStack) {
    printf("Recently Returned Books:\n");
    Stack temp = recentStack;
    // Traverse the queue and print each user request
    while (temp != NULL) {
        printf("ID: %d, Title: %s, Author: %s\n", temp->Data.bookID, temp->Data.title, temp->Data.author);
        temp = temp->Next;
    }
}

void DisplayQueue(Queue requestQueue) {
    printf("Borrow Request Queue:\n");
    EQueue temp = requestQueue.Head;
    while (temp != NULL) {
        printf("User ID: %d, Name: %s, Requested Book ID: %d\n", temp->Data.userID, temp->Data.name, temp->Data.requestedBookID);
        temp = temp->Next;
    }
}


// Function to search for a book in the inventory
void SearchBook(Book *inventory, int count) {
    int bookID;
    printf("Enter Book ID to Search: ");
    scanf("%d", &bookID);
    for (int i = 0; i < count; i++) {
         // Search for the book and print its details
        if (inventory[i].bookID == bookID) {
            printf("Book Found - ID: %d, Title: %s, Author: %s, Status: %s\n",
                   inventory[i].bookID, inventory[i].title, inventory[i].author,
                   inventory[i].isAvailable ? "Available" : "Unavailable");
            return;
        }
    }
    printf("Book Not Found!\n");
}

int main() {
    Book *inventory = NULL;    // Inventory of books
    int bookCount = 0;         // Number of books
    Queue requestQueue;        // Borrow request queue
    Stack recentStack;         // Recently returned books stack


// Initialize the queue and stack
    InitQueue(&requestQueue);
    InitStack(&recentStack);

    // Initialize library with sample data
    InitializeLibrary(&inventory, &bookCount, &recentStack, &requestQueue);

    int choice;
    do {
         // Display the menu

        printf("\nLibrary Menu:\n");
        printf("1. Add New Book\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. View Recently Returned Books\n");
        printf("5. Display Borrow Request Queue\n");
        printf("6. Process Borrow Requests\n");
        printf("7. Search for a Book\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
                     // Handle user choice
        switch (choice) {
            case 1: AddBook(&inventory, &bookCount); break;
            case 2: BorrowBook(inventory, bookCount, &requestQueue); break;
            case 3: ReturnBook(inventory, bookCount, &recentStack); break;
            case 4: DisplayStack(recentStack); break;
            case 5: DisplayQueue(requestQueue); break;
            case 6: ProcessRequests(inventory, bookCount, &requestQueue); break;
            case 7: SearchBook(inventory, bookCount); break;
            case 8: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 8);

    free(inventory);  // Free allocated memory
    return 0;
}

