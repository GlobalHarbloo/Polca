#ifndef CALC_H
#define CALC_H

#include "stack.h"

double evaluate_rpn(char *expression, double x);
int is_operator(const char *token);
int is_function(const char *token);
double apply_function(const char *function, double operand);
double apply_operator(const char *operator, double operand1, double operand2);
void stack_free(Stack *stack);
#endif