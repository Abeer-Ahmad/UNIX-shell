#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "environment.h"
#include <stdio.h>

#define ENV_VAR_SIZE 4
#define MAX_PATHS 20

environment_variable var_table[ENV_VAR_SIZE];
char *paths[MAX_PATHS];
int n_paths = 0;
char *history_path;
char *logs_path;

void set_paths();
void set_files();

void setup_environment() {
    var_table[0].name = "PATH";
    var_table[0].value = getenv("PATH");

    var_table[1].name = "HOME";
    var_table[1].value = getenv("HOME");

    var_table[2].name = "CWD"; // currently working directory, initially "Home"
    var_table[2].value = getenv("HOME"); // check

    var_table[3].name = "PD"; // project directory
    var_table[3].value = getcwd(var_table[3].value, 200); // check

    set_paths();
    set_files();
}

void update_environment(char *var_name, char *value) {
    for (int i = 0; i < ENV_VAR_SIZE; i++)
        if (!strcmp(var_name, var_table[i].name)) { // shell_variable already exists
            var_table[i].value == value; // update value
            return;
        }
}

char *get_environment_variable(char *name) {
    for (int i = 0; i < ENV_VAR_SIZE; i++)
        if (!strcmp(name, var_table[i].name))
            return var_table[i].value;
    return NULL;
}

char *get_history_path() {
    return history_path;
}

char *get_logs_path() {
    return logs_path;
}

char **get_paths() {
    return paths;
}

int get_paths_count() {
    return n_paths;
}

void set_paths() {
    int PATH_length = strlen(get_environment_variable("PATH"));
    char *PATH = malloc(PATH_length + 1); // if not allocated, paths[] has garbage values when used later -must not be freed-
    PATH[PATH_length] = '\0';
    strcpy(PATH, get_environment_variable("PATH"));
    char *path = strtok (PATH, ":");
    while (path != NULL) {
        paths[n_paths++] = path;
        path = strtok (NULL, ":");
    }
    paths[n_paths++] = "/";
}

void set_files() {
    char *project_directory = get_environment_variable("PD");
    int length = strlen(project_directory);

    history_path = malloc(length + 9); // for "/history" + '\0'
    history_path[length + 8] = '\0';
    strcpy(history_path, project_directory);
    strcat(history_path, "/history");

    logs_path = malloc(length + 6);
    logs_path[length + 5] = '\0';
    strcpy(logs_path, project_directory);
    strcat(logs_path, "/logs");
}