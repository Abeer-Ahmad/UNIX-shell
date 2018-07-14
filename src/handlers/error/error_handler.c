#include <stdio.h>
#include "error_handler.h"

void print_error_message(char *message) {
    printf(RED "%s\n", message);
    printf(DEFAULT);
}