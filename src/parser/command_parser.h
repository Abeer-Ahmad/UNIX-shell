#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stdbool.h>

typedef struct {
    bool is_assignment;
    bool is_in_background;
    bool has_error;
    char *error_message;
} Properties;

char **parse(char command[]); // splits the given command to separate argument; to be sent to execv()

Properties get_properties(); // returns a set of flags, describing the parsed command

#endif
