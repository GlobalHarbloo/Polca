#ifndef STACK_H
#define STACK_H

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Stack *stack_init();
char is_stack_empty(Stack *stack);
void push(Stack *stack, char *data);
char *pop(Stack *stack);
#endif