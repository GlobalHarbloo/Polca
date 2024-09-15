#include "calc.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

double evaluate_rpn(char *expression, double x) {
    Stack *stack = stack_init();
    char *token = strtok(expression, " ");

    while (token != NULL) {
        if (strcmp(token, "x") == 0) {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%lf", x);
            char *buf_dup = strdup(buffer);
            push(stack, buf_dup);
            free(buf_dup);
        } else if (is_operator(token)) {
            char *operand2_str = pop(stack);
            char *operand1_str = pop(stack);
            double operand2 = atof(operand2_str);
            double operand1 = atof(operand1_str);
            double result = apply_operator(token, operand1, operand2);
            char result_str[32];
            snprintf(result_str, sizeof(result_str), "%lf", result);
            char *res_dup = strdup(result_str);
            push(stack, res_dup);
            free(res_dup);
            free(operand1_str);
            free(operand2_str);
        } else if (is_function(token)) {
            char *operand_str = pop(stack);
            double operand = atof(operand_str);
            double result = apply_function(token, operand);
            char result_str[32];
            snprintf(result_str, sizeof(result_str), "%lf", result);
            char *res_dup = strdup(result_str);
            push(stack, res_dup);
            free(res_dup);
            free(operand_str);
        } else {
            char *token_str = strdup(token);
            push(stack, token_str);
            free(token_str);
        }
        token = strtok(NULL, " ");
    }

    char *result_str = pop(stack);
    double result = atof(result_str);
    free(result_str);
    stack_free(stack);
    return result;
}

int is_operator(const char *token) {
    return strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 ||
           strcmp(token, "/") == 0;
}

int is_function(const char *token) {
    return strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0 ||
           strcmp(token, "sqrt") == 0 || strcmp(token, "ln") == 0;
}

double apply_operator(const char *operator, double operand1, double operand2) {
    double flag = 0.0;
    if (strcmp(operator, "+") == 0) {
        flag = operand1 + operand2;
    } else if (strcmp(operator, "-") == 0) {
        flag = operand1 - operand2;
    } else if (strcmp(operator, "*") == 0) {
        flag = operand1 * operand2;
    } else if (strcmp(operator, "/") == 0) {
        flag = operand1 / operand2;
    }
    return flag;
}

double apply_function(const char *function, double operand) {
    double flag = 0.0;
    if (strcmp(function, "sin") == 0) {
        flag = sin(operand);
    } else if (strcmp(function, "cos") == 0) {
        flag = cos(operand);
    } else if (strcmp(function, "tan") == 0) {
        flag = tan(operand);
    } else if (strcmp(function, "sqrt") == 0) {
        flag = sqrt(operand);
    } else if (strcmp(function, "ln") == 0) {
        flag = log(operand);
    }
    return flag;
}

void stack_free(Stack *stack) {
    while (!is_stack_empty(stack)) {
        free(pop(stack));
    }
    free(stack);
}
