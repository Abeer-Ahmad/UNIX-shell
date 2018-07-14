#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

typedef struct {
    char *name;
    char *value;
} environment_variable;

void setup_environment(); // must be called at the beginning of the program

void update_environment(char *var_name, char *value); // especially, for "cd" commands

char *get_environment_variable(char *name);

char *get_history_path();

char *get_logs_path();

char **get_paths();

int get_paths_count();

#endif

