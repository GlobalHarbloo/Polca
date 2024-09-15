#ifndef POLCA_H
#define POLCA_H

char *polka(char *input, Stack *stack);
void check_priority(Stack *stack, const char *current, char *str_output);

double evaluate_rpn(char *expression, double x);
int is_operator(const char *token);
int is_function(const char *token);
double apply_operator(const char *operator, double operand1, double operand2);
double apply_function(const char *function, double operand);
void stack_free(Stack *stack);

#endif