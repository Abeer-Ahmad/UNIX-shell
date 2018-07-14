#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <wait.h>
#include "process.h"
#include "../variables/environment.h"

void try_paths(char **args);
void *set_cur_path(char *cur_path, char *temp, int temp_length, char *command, int command_length);

void execute(char **args, bool in_background) {
    pid_t pid = fork();
    if (!pid)
        try_paths(args);
    else
        if (!in_background) {
            int status;
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
}

void try_paths(char **args) {
    char *temp;
    int temp_length, command_length = strlen(args[0]), i = 0;
    char **paths = get_paths();
    int n_paths = get_paths_count();
    while (i < n_paths) {
        temp = paths[i];
        temp_length = strlen(temp);
        char cur_path[temp_length + command_length + 2]; // 2 for '/' and '\0'
        set_cur_path(cur_path, temp, temp_length, args[0], command_length);
        execv(cur_path, args);
        i++;
    }
    fprintf(stderr, "Error: %s\n", strerror(errno));
    abort();
}

void *set_cur_path(char *cur_path, char *temp, int temp_length, char *command, int command_length) {
    cur_path [temp_length + command_length + 1] = '\0';
    strcpy(cur_path, temp);
    cur_path[temp_length] = '/';
    strncpy(&cur_path[temp_length + 1], command, command_length);
}