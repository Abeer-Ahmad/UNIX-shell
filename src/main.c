#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <signal.h>
#include "parser/command_parser.h"
#include "datastructures/linked_list.h"
#include "variables/environment.h"
#include "handlers/command/command_handler.h"
#include "handlers/file/file_handler.h"
#include "handlers/error/error_handler.h"

#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define DEFAULT "\x1b[0m"

void start_shell(FILE *stream, bool interactive_mode);
char *read_line(char *command, size_t max_bytes, FILE *stream);

void sig_handler(int sig) {
    FILE *logs = get_file(get_logs_path(), "a");
    write_to_file(logs, "Child Process Was Terminated...");
    close_file(logs);
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &sig_handler;
    sigaction(SIGCHLD, &sa, NULL);

    setup_environment();
    chdir(get_environment_variable("HOME"));
    if (argc == 1) { // Interactive Mode
        start_shell(stdin, true);
    } else if (argc == 2) { // Batch Mode
        FILE *batch_file = get_file(argv[1], "r");
        start_shell(batch_file, false);
    } else {
        print_error_message("ERROR: TOO MANY ARGUMENTS!");
        return 1;
    }
}

void start_shell(FILE *stream, bool interactive_mode) {
    char *command, *return_value;
    size_t max_bytes = 513;
    command = malloc(max_bytes);
    while (true) {
        if (interactive_mode)
            printf(CYAN "Shell> " DEFAULT);
        return_value = read_line(command, max_bytes, stream);
        if (!strcmp(command, "exit") || return_value == NULL) { // NULL means that getline() has encountered EOF
            printf(MAGENTA "Exiting Shell...\n");
            if (!interactive_mode)
                close_file(stream);
            exit(0);
        }
        handle_command(command);
    }
}

char *read_line(char *command, size_t max_bytes, FILE *stream) {
    ssize_t bytes_read = getline(&command, &max_bytes, stream);
    if (bytes_read == -1) // EOF
        return NULL;
    command[bytes_read - 1] = '\0'; // replacing the new line '\n' with a null terminator '\0'
    return command;
}