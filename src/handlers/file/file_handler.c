#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <stdlib.h>
#include "file_handler.h"

FILE *get_file(char *file_path, char *mode) {
    FILE *file = fopen(file_path, mode);
    if (file == NULL) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(1);
    }
}

void close_file(FILE *file) {
    fclose(file);
}

void write_to_file(FILE *file, char *new_entry) {
    fprintf(file, "%s\n", new_entry);
}
