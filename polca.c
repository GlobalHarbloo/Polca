#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "stack.h"

int get_operator_priority(const char *operator) {
    int flag = 0;
    if (strcmp(operator, "sqrt") == 0 || strcmp(operator, "ln") == 0) {
        flag = 4;
    } else if (strcmp(operator, "*") == 0 || strcmp(operator, "/") == 0) {
        flag = 3;
    } else if (strcmp(operator, "+") == 0 || strcmp(operator, "-") == 0) {
        flag = 2;
    } else if (strcmp(operator, "sin") == 0 || strcmp(operator, "cos") == 0 || strcmp(operator, "tan") == 0) {
        flag = 5;
    } else if (strcmp(operator, "(") == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    return flag;
}

void check_priority(Stack *stack, const char *current, char *str_output) {
    int priority = get_operator_priority(current);
    int exit_loop = 0;
    while (!is_stack_empty(stack) && !exit_loop) {
        char *last = pop(stack);
        int priority_last = get_operator_priority(last);

        if (priority_last >= priority) {
            strcat(str_output, last);
            free(last);
            strcat(str_output, " ");
        } else {
            push(stack, last);
            exit_loop = 1;
            free(last);
        }
    }
    char *cur_dup = strdup(current);
    push(stack, cur_dup);
    free(cur_dup);
}

char *polka(char *input, Stack *stack) {
    char *str_output = (char *)malloc(strlen(input) * 2 + 1);
    str_output[0] = '\0';
    int i = 0;
    int size = strlen(input);
    while (i < size) {
        char current = input[i];
        char current_1 = input[i - 1];
        if (current == 's' && strncmp(&input[i], "sin", 3) == 0) {
            i += 3;
            const char *current_op = "sin";
            check_priority(stack, current_op, str_output);
        } else if (current == 's' && strncmp(&input[i], "sqrt", 4) == 0) {
            i += 4;
            const char *current_op = "sqrt";
            check_priority(stack, current_op, str_output);
        } else if (current == 'c' && strncmp(&input[i], "cos", 3) == 0) {
            i += 3;
            const char *current_op = "cos";
            check_priority(stack, current_op, str_output);
        } else if (current == 't' && strncmp(&input[i], "tan", 3) == 0) {
            i += 3;
            const char *current_op = "tan";
            check_priority(stack, current_op, str_output);
        } else if (current == 'l' && strncmp(&input[i], "ln", 2) == 0) {
            i += 2;
            const char *current_op = "ln";
            check_priority(stack, current_op, str_output);
        } else if ((current >= '0' && current <= '9')) {
            while ((current >= '0' && current <= '9') && i < size) {
                strncat(str_output, &current, 1);
                current = input[++i];
            }
            strcat(str_output, " ");
        } else if (current == '+' || current == '*' || current == '/') {
            const char current_op[2] = {current, '\0'};
            check_priority(stack, current_op, str_output);
            i++;
        } else if (current == '-') {
            if (current_1 == '(') {
                const char *current_op = "-";
                strcat(str_output, "0");
                strcat(str_output, " ");
                check_priority(stack, current_op, str_output);
                i++;
            } else {
                const char *current_op = "-";
                check_priority(stack, current_op, str_output);
                i++;
            }

        } else if (current == ')') {
            char *last = NULL;
            while (!is_stack_empty(stack) && strcmp(last = pop(stack), "(") != 0) {
                strcat(str_output, last);
                free(last);
                strcat(str_output, " ");
            }
            free(last);
            i++;
        } else if (current == '(') {
            push(stack, "(");
            i++;
        } else if (current == 'x') {
            strncat(str_output, &current, 1);
            strcat(str_output, " ");
            i++;
        } else {
            i++;
        }
    }
    while (!is_stack_empty(stack)) {
        char *last = pop(stack);
        strcat(str_output, last);
        free(last);
        strcat(str_output, " ");
    }
    return str_output;
}
