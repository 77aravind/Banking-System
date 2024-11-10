#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a customer request
typedef struct {
    int id;
    char type[20];  // Request type: "deposit", "withdrawal", "inquiry"
} CustomerRequest;

// Node structure for the queue
typedef struct Node {
    CustomerRequest data;
    struct Node* next;
} Node;

// Queue structure
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Function to enqueue a new customer request
void enqueue(Queue* q, int id, char* type) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data.id = id;
    strcpy(temp->data.type, type);
    temp->next = NULL;
    if (isEmpty(q)) {
        q->front = temp;
    } else {
        q->rear->next = temp;
    }
    q->rear = temp;
    printf("Added customer %d with request: %s\n", id, type);
}

// Function to dequeue a customer request
void dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty, no requests to process.\n");
        return;
    }
    Node* temp = q->front;
    printf("Processing customer %d request: %s\n", temp->data.id, temp->data.type);
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}

// Main function with user input
int main() {
    Queue q = {NULL, NULL};  // Initialize queue
    int choice;

    printf("Banking System Simulation\n");
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Add a customer request\n");
        printf("2. Process next request\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int id;
            char type[20];
            printf("Enter customer ID: ");
            scanf("%d", &id);
            printf("Enter request type (deposit, withdrawal, inquiry): ");
            scanf("%s", type);

            enqueue(&q, id, type);
        } else if (choice == 2) {
            dequeue(&q);
        } else if (choice == 3) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}