#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//definition of a task structure
typedef struct task {
int id;  //unique task identifier
char description[200]; //description of the task
int priority; //1--5
char status[20]; //"pending",,"in progress",,"completed"
struct task*next; //pointer to the nest task
} task;

//function task insertion
task* insertt(task* head, int id ,const char* description, int priority, const char* status){
   task* newtask = (task*)malloc(sizeof(task));  //allocate memory for new task


   newtask->id = id;      //assign the task id
   strcpy(newtask->description, description); //copy the description
   newtask->priority = priority ; // assign the priority
   strcpy(newtask->status, status);  //copy the status
   newtask->next =NULL;

           //insert the task into the correct position in the list in order of priority
   if (head == NULL || head->priority < priority ){

      newtask->next = head;          //if the list is empty or the task has the highest priority
      head = newtask;                 // it becomes the new head

   } else {
                 //traverse the list to find the position
     task* current = head;       //starts from the head of the list
     while (current->next != NULL && current->next->priority >= priority) {
        current = current->next;  //move the pointer to the next node

     }
     newtask->next= current->next;  //insert the task (correct position),, link the new task to the next node
     current->next = newtask;   // Link the current node to the new task

   }

printf("Task with ID %d added successfully!\n", id); // Notify the user
    return head; // Return the updated head of the list
}





// Function task deletion
task* deletet(task* head, int id) {
    if (head == NULL) {
            // If the list is empty
        printf("task list is empty. Nothing to delete.\n");
        return NULL;
    }

       // If the task to delete is the first task in the list
    if (head->id == id) {
        task* temp = head; // Save the head
        head = head->next; // Move the head to the next task
        free(temp); // Free the memory of the old head
        printf("task with ID %d deleted successfully!\n", id);
        return head;
    }

    // Traverse the list to find the task
    task* current = head;
    while (current->next != NULL && current->next->id != id) {
        current = current->next;  //move to the next node
    }

    if (current->next != NULL) { // If the task is found
        task* temp = current->next; // Save the task
        current->next = current->next->next; // Remove the task from the list
        free(temp); // Free the memory
        printf("task with ID %d deleted successfully!\n", id);
    }
     else {
        printf("Task with ID %d not found.\n", id);  //the given id does not exit in the list
    }

    return head;
}


// Function to update the status of a task
void updateS(task* head, int id, const char* newstatus) {
    task* current = head; // Start from the head of the list
    while (current != NULL) {
            // Traverse the list
        if (current->id == id) {
                // If the task with the given ID is found
            strcpy(current->status, newstatus); // Update the status
            printf("task with ID %d status updated to '%s'.\n", id, newstatus);
            return;
        }
        current = current->next;
    }
    printf("task with ID %d not found. Status not updated.\n", id);  //the given id does not exist in the list
}

    // Function to display tasks grouped by status
void displayt(task* head) {
    // Check if the list is empty
    if (head == NULL) {
        printf("No tasks in the list.\n");
        return;  // Exit if there are no tasks
    }

    // Create three separate lists for different statuses
    task* pendingHead = NULL;
    task* inProgressHead = NULL;
    task* completedHead = NULL;

    // Traverse the original list and classify tasks based on their status
    task* current = head;
    while (current != NULL) {
        // Classify the task based on its status
        if (strcmp(current->status, "Pending") == 0) {
            pendingHead = insertt(pendingHead, current->id, current->description, current->priority, current->status);
        } else if (strcmp(current->status, "In Progress") == 0) {
            inProgressHead = insertt(inProgressHead, current->id, current->description, current->priority, current->status);
        } else if (strcmp(current->status, "Completed") == 0) {
            completedHead = insertt(completedHead, current->id, current->description, current->priority, current->status);
        } else {
            printf("Invalid status found for task with ID: %d\n", current->id);
        }
        current = current->next;  // Move to the next task in the list
    }


    // Helper function to print a list of tasks
void printList(task* head) {
    task* current = head;
    while (current != NULL) {  // Traverse through the list of tasks
        // Print the details of the current task
        printf("ID: %d, Desc: %s, Priority: %d, Status: %s\n",
               current->id, current->description, current->priority, current->status);
        current = current->next;  // Move to the next task in the list
    }
}



    // Display tasks for each status
    printf("\nPending Tasks:\n");
    if (pendingHead == NULL) {
        printf("No tasks pending.\n");
    } else {
        printList(pendingHead);  // Print tasks with "Pending" status
    }

    printf("\nIn Progress Tasks:\n");
    if (inProgressHead == NULL) {
        printf("No tasks in progress.\n");
    } else {
        printList(inProgressHead);  // Print tasks with "In Progress" status
    }

    printf("\nCompleted Tasks:\n");
    if (completedHead == NULL) {
        printf("No tasks completed.\n");
    } else {
        printList(completedHead);  // Print tasks with "Completed" status
    }
}






// Function to search tasks by their priority
void searchByPriority(task* head, int priority) {
    task* current = head; // Start from the head of the list
    int found = 0;
    printf("tasks with priority %d:\n", priority);
    while (current != NULL) {
        if (current->priority == priority) { // If the task has the given priority
            printf("ID: %d, Desc: %s, Status: %s\n", current->id, current->description, current->status);
            found = 1;
        }
        current = current->next;
    }
    if (!found) printf("No tasks found with priority %d.\n", priority);

}
task* createInitialList() {
    task* head = NULL;

    // Adding some predefined tasks
    head = insertt(head, 1, "Task 1: firsttask", 3, "Pending");
    head = insertt(head, 2, "Task 2: secondtask", 5, "In Progress");
    head = insertt(head, 3, "Task 3: thirdtask", 4, "Pending");
    head = insertt(head, 4, "Task 4: fourthtask", 2, "Completed");
    head = insertt(head, 5, "Task 5: fifthtask", 1, "Pending");

    printf("Initial task list created successfully!\n");
    return head;
}

// Main function
int main() {
    task* head = NULL; // Declare the list

    // Call the function to create an initial list
    head = createInitialList();

    int choice, id, priority;
    char description[200], status[20];

    do {
        // Display the menu
        printf("\nMenu:\n");
        printf("1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. Update Task Status\n");
        printf("4. Display All Tasks\n");
        printf("5. Search Tasks by Priority\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: // Add a task
            printf("Enter ID, description, priority (1-5), and status: ");
            scanf("%d %s %d %s", &id, description, &priority, status);
            head = insertt(head, id, description, priority, status);
            break;
        case 2: // Delete a task
            printf("Enter ID of task to delete: ");
            scanf("%d", &id);
            head = deletet(head, id);
            break;
        case 3: // Update the status of a task
            printf("Enter ID and new status: ");
            scanf("%d %s", &id, status);
            updateS(head, id, status);
            break;
        case 4: // Display all tasks
            displayt(head);
            break;
        case 5: // Search tasks by priority
            printf("Enter priority to search for: ");
            scanf("%d", &priority);
            searchByPriority(head, priority);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}





