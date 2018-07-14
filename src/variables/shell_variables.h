#ifndef SHELL_VARIABLES_H
#define SHELL_VARIABLES_H

typedef struct {
    char *name;
    char *value;
} shell_variable;

void set_variable(char *name, char *value);

char *get_variable(char *var_name);

#endif
