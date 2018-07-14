#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

FILE *get_file(char *file_path, char *mode);

void close_file(FILE *file);

void write_to_file(FILE *file, char *new_entry);

#endif

