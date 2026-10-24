#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char data;
    struct Node * next;
} Node;

typedef struct Stack {
    Node * top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
}
int isEmpty(Stack* s) {
    if(s->top == NULL)
        return 1;
    else
        return 0;
}
void push(Stack* s, char value) {
    Node* newNode = (Node*)malloc(sizeof(*newNode));
    if(newNode == NULL) {
        printf("memory allocation failed\n");
        return;
    } else {
        newNode->data = value;
        newNode->next = s->top;
        s->top = newNode;
    }
}
char pop(Stack* s) {
    if (!isEmpty(s)) {
        Node* temp;
        temp = s->top;
        char value = temp->data;
        s->top = s->top->next;
        free(temp);
        return value;
    } else {
        printf("the stack is empty\n");
    }
    return '\0'; 
}
//same as pop just see whats in the top without removing
char peek(Stack* s) {
    if(!isEmpty(s))
        return s->top->data;
    else {
        printf("the stack is empty\n");
        return '\0';
    }
}
int expr(Stack*s,char expretion[])
{
    int i=0;
    int result=0;
    while (expretion[i]!='\0')
    {
       switch (expretion[i])
       {
       case '+':
       {
        int x=pop(s)-'0';
        int y=pop(s)-'0';
        result=y+x;
        push(s,result+ '0');i++;
        break;
       }
       case '-':
       {
        int x=pop(s)-'0';
        int y=pop(s)-'0';
        result=y-x;
        push(s,result+ '0');i++;
        break;
       }case '*':
       {
        int x=pop(s)-'0';
        int y=pop(s)-'0';
        result=y*x;
        push(s,result+ '0');i++;
        break;
       }case '/':
       {
        int x=pop(s)-'0';
        int y=pop(s)-'0';
        result=y/x;
        push(s,result+'0');i++;
        break;
       }
       case ' ':
       {i++;
        continue;
       }
       default:
       {
        push(s,expretion[i]);i++;
        break;
       }
       }
    }
  return pop(s)-'0';   
}
void display(Stack* s) {
    if(!isEmpty(s)) {
        Node *current;
        current = s->top;
        while(current != NULL) {
            printf("%c", current->data);
            current = current->next;
        }
    } else {
        printf("the stack is empty\n");
        return;
    }
}
int main() {    
    Stack s;
    int choice;
    bool run = true;
    char value;         
    initStack(&s);
    while (run) {
        printf("\n===== STACK MENU =====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. expretion\n");
        printf("6. exit\n");
        printf("Enter your choice: ");   
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("Enter a character: ");
                scanf(" %c", &value);
                push(&s, value);
                break;
            }
            case 2: {
                char v = pop(&s);
                if (v != '\0') 
                    printf("Popped: %c\n", v);
                break;
            }  
            case 3: {
                char v = peek(&s);
                if (v != '\0') 
                    printf("peeked: %c\n", v);
                break;
            }
            case 4: {
                printf("====================================\n");
                display(&s);
                printf("\n====================================\n");
                break;
            }
            case 5: {
                initStack(&s); 
                char expression[50];
                printf("Enter postfix expression: ");
                scanf(" %[^\n]",expression); 
                int result = expr(&s,expression);
                printf("Result: %d\n",result);
                break;
            }
            case 6: {
                run = false;
                printf("goodbye\n");
                break;
            }
            default:
                printf("thats invalid choice !!!\n");
        }
    }
    return 0;
}
