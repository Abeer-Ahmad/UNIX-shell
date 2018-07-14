#include <stdbool.h>
#include "pre_parser.h"
#include "../datastructures/string.h"

bool is_command(char *command, int length);

int get_status(char *command, int length) {
    if (length > MAX_LENGTH)
        return -1;
    if (!length || !is_command(command, length)) // empty, spaces-only, or comment
        return 0;
    return 1;
}

bool is_command(char *command, int length) {
    for (int i = 0; i < length; ++i) {
        if (is_space(command[i]))
            continue;
        else if (command[i] == '#')
            return false;
        else
            return true;
    }
    return false;
}