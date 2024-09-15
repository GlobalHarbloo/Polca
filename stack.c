#include "stack.h"

#include <stdlib.h>
#include <string.h>

Stack *stack_init() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

char is_stack_empty(Stack *stack) { return stack->top == NULL; }

void push(Stack *stack, char *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = strdup(data);
    new_node->next = stack->top;
    stack->top = new_node;
}

char *pop(Stack *stack) {
    Node *temp = stack->top;
    char *data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return data;
}
