
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "polca.h"
#include "stack.h"

int main() {
    char str[100];
    if (fgets(str, sizeof(str), stdin) == NULL) {
        perror("Error reading input");
        return EXIT_FAILURE;
    }

    Stack *stack = stack_init();
    char *str_it = polka(str, stack);
    if (str_it == NULL) {
        fprintf(stderr, "Error converting infix to postfix\n");
        return EXIT_FAILURE;
    }

    double grad = M_PI / 20;
    double y_step = 0.08;
    double tolerance = 0.04;

    for (double y = -1.0; y <= 1.0; y += y_step) {
        for (double x = 0.0; x <= 4 * M_PI; x += grad) {
            char *str_cpy = strdup(str_it);
            if (str_cpy == NULL) {
                perror("Failed to duplicate string");
                free(str_it);
                free(stack);
                return EXIT_FAILURE;
            }

            double result = evaluate_rpn(str_cpy, x);

            if (fabs(result - y) < tolerance) {
                printf("*");
            } else {
                printf(".");
            }

            free(str_cpy);
        }
        printf("\n");
    }

    free(str_it);
    stack_free(stack);
    return 0;
}
