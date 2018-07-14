#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
#include "../handlers/file/file_handler.h"
#include "../variables/environment.h"

void cd(char *path) {
    chdir(path);
}

void history() {
    FILE *history = get_file(get_history_path(), "r");
    size_t max_bytes = 513;
    char *entry = malloc(max_bytes);
    while (getline(&entry, &max_bytes, history) != -1)
        printf("%s", entry);
    close_file(history);
    free(entry);
}
