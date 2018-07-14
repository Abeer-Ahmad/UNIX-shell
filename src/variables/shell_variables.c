#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "shell_variables.h"
#include "../handlers/error/error_handler.h"

#define MAX_SHELL_VAR 100

shell_variable shell_table[MAX_SHELL_VAR];
int size = 0;

char *copy(char *temp);

void set_variable(char *name, char *value) {
    if (size == MAX_SHELL_VAR) {
        print_error_message("ERROR: YOU HAVE EXCEEDED THE MAXIMUM NUMBER OF VARIABLES!");
        return;
    }
    for (int i = 0; i < size; i++)
        if (!strcmp(name, shell_table[i].name)) { // shell_variable already exists
            shell_table[i].value = copy(value); // update value
            return;
        }
    shell_table[size].name = copy(name);
    shell_table[size++].value = copy(value);
}

char *get_variable(char *var_name) {
    for (int i = 0; i < size; i++)
        if (!strcmp(var_name, shell_table[i].name))
            return shell_table[i].value;
    return NULL;
}

char *copy(char *temp) {
    int length = strlen(temp);
    char *copy = malloc(length + 1);
    copy[length] = '\0';
    strcpy(copy, temp);
    return copy;
}