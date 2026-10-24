#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queueNode {
    int customerNumber;
    struct queueNode* next;
} queueNode;

typedef struct Queue {
    queueNode* front;
    queueNode* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmptyQueue(Queue* q) {
    if (q->front == NULL) return 1;
    else return 0;
}

void enqueue(Queue* q, int number) {
    queueNode* newNode = (queueNode*)malloc(sizeof(*newNode));
    if(newNode == NULL) {
        printf("\nMemory allocation failed!\n");
        return;
    }
    newNode->customerNumber = number;
    newNode->next = NULL;

    if (q->front == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue* q) {
    if (!isEmptyQueue(q)) {
        queueNode* temp = q->front;
        int number = temp->customerNumber;
        q->front = q->front->next;
        
        if (q->front == NULL) {
            q->rear = NULL;
        }
        free(temp);
        return number;
    } else {
        printf("\n[WARNING] The queue is empty.\n");
    }
    return -1; 
}

int peekQueue(Queue* q) {
    if(!isEmptyQueue(q)) return q->front->customerNumber;
    else {
        printf("\n[WARNING] The queue is empty.\n");
        return -1;
    }
}

void displayQueue(Queue* q) {
    if(!isEmptyQueue(q)) {
        queueNode* current = q->front;
        while(current != NULL) {
            printf("[%d] ", current->customerNumber);
            current = current->next;
        }
        printf("\n");
    } else {
        printf("\n[QUEUE] No customers waiting.\n");
    }
}

int main() {    
    Queue q;
    int choice;
    bool run = true;
    int value;         
    
    initQueue(&q);

    while (run) {
        printf("\n====================================\n");
        printf("        BANK QUEUE MANAGEMENT       \n");
        printf("====================================\n");
        printf(" 1. Add Customer (Enqueue)\n");
        printf(" 2. Serve Customer (Dequeue)\n");
        printf(" 3. View Next Customer (Peek)\n");
        printf(" 4. View All Waiting Customers\n");
        printf(" 5. Start Bank Simulation\n");
        printf(" 6. Exit Program\n");
        printf("====================================\n");
        printf(" Enter your choice: ");   
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                printf("\nEnter customer number: ");
                scanf("%d", &value);
                enqueue(&q, value);
                printf("-> Customer %d added to the queue.\n", value);
                break;
            }
            case 2: {
                int v = dequeue(&q);
                if (v != -1) 
                    printf("\n-> Customer %d has been served.\n", v);
                break;
            }  
            case 3: {
                int v = peekQueue(&q);
                if (v != -1) 
                    printf("\n-> Next in line: Customer %d\n", v);
                break;
            }
            case 4: {
                printf("\n--- Customers in Queue ---\n");
                displayQueue(&q);
                printf("---------------------------\n");
                break;
            }
            case 5: {
                initQueue(&q);
                int ticket = 0;
                bool bankOpen = true;
                int simChoice;
                
                printf("\n====================================\n");
                printf("        BANK SIMULATION MODE        \n");
                printf("====================================\n");
                
                while (bankOpen) {
                    printf("\n--- SIMULATION MENU ---\n");
                    printf(" 1. Add New Customer\n");
                    printf(" 2. Serve Next Customer\n");
                    printf(" 3. Close Bank & Exit\n");
                    printf("-----------------------\n");
                    printf(" Enter choice: ");
                    scanf("%d", &simChoice);
                    
                    switch(simChoice) {
                        case 1:
                            ticket++;
                            enqueue(&q, ticket);
                            printf("\n>> Customer %d arrived and got a token.\n", ticket);
                            break;
                        case 2:
                            if (!isEmptyQueue(&q)) {
                                printf("\n>> Customer %d is being served.\n", dequeue(&q));
                            } else {
                                printf("\n>> No customers are waiting.\n");
                            }
                            break;
                        case 3:
                            bankOpen = false;
                            printf("\n>> Closing the bank...\n");
                            break;
                        default:
                            printf("\n[ERROR] Invalid choice.\n");
                    }
                }
                
                printf("\n--- End of Day ---\n");
                while (!isEmptyQueue(&q)) {
                    printf(">> Customer %d is being served.\n", dequeue(&q));
                }
                printf("\n>> All customers served.\n");
                printf(">> The bank is now closed.\n");
                break;
            }
            case 6: {
                run = false;
                printf("\n>> Exiting program. Have a good day!\n");
                break;
            }
            default:
                printf("\n[ERROR] Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
