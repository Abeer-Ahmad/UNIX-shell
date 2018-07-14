#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include "command_parser.h"
#include "../datastructures/linked_list.h"
#include "../variables/environment.h"
#include "../variables/shell_variables.h"
#include "../datastructures/string.h"

#define DOUBLE_QUOTES '"'

List *arg_list = NULL;
Properties properties;

void reset();
void check_background(char command[]);
void copy_argument(char *command, int j, int count);
void replace_special_characters(char *temp);
int replace_home(char *argument, int j);
char *extract_var(char *temp, int temp_length, int i);
int replace_var(char *argument, char *var_name, int j);
void handle_assignment(char *argument, char *temp, int temp_length, int j);
bool check_var_name(char *argument);

char **parse(char command[]) {
    reset();
    check_background(command);
    split(command);
    return to_array(arg_list);
}

Properties get_properties() {
    return properties;
}

void check_background(char command[]) {
    int i = strlen(command) - 1;
    while (is_space(command[i])) // find the last non-blank character
        i--;
    if (command[i] == '&') {
        properties.is_in_background = true;
        command[i] = '\0';
    }
}

void split(char command[]) {
    int j, start, count, command_length = strlen(command);
    bool between_quotes;
    for (int i = 0; i < command_length; i++) {
        if (is_space(command[i]))
            continue;
        count = 0, start = i;
        between_quotes = false;
        for (j = start; (j < command_length && (!is_space(command[j]) || (is_space(command[j]) && between_quotes))); j++) {
            if (command[j] == DOUBLE_QUOTES)
                between_quotes = !between_quotes;
            else
                count++;
        }
        i = j;
        copy_argument(command, start, count);
    }
}

void copy_argument(char *command, int j, int count) {
    char *temp_argument = malloc(count + 1);
    int i = 0;
    while (i < count) {
        if (command[j] != DOUBLE_QUOTES)
            temp_argument[i++] = command[j];
        j++;
    }
    temp_argument[i] = '\0';
    replace_special_characters(temp_argument);
}

void replace_special_characters(char *temp) {
    char *argument = malloc(1000);
    int j = 0, temp_length = strlen(temp);
    for (int i = 0; i < temp_length; i++) {
        if (temp[i] == '~') { // home
            j = replace_home(argument, j);
        } else if (temp[i] == '$') { // shell_variable
            char *var_name = extract_var(temp, temp_length, i + 1);
            i += strlen(var_name);
            j = replace_var(argument, var_name, j);
            if (j == -1) {
                properties.has_error = true;
                properties.error_message = "ERROR: UNDECLARED VARIABLE!";
                return;
            }
        } else if (temp[i] == '=') {
            properties.is_assignment = true;
            break;
        } else {
            argument[j++] = temp[i];
        }
    }
    argument[j] = '\0';
    argument = realloc(argument, j + 1); // reallocating the proper memory space
    if (properties.is_assignment) {
        handle_assignment(argument, temp, temp_length, j);
        return;
    }
    add(arg_list, argument);
    free(temp); // getting rid of the old-version argument
}

int replace_home(char *argument, int j) {
    char *home = get_environment_variable("HOME");
    int length = strlen(home);
    for (int k = 0; k < length; k++) // append home path, ignoring the leading '/'?
        argument[j++] = home[k];
    return j;
}

char *extract_var(char *temp, int temp_length, int i) {
    char *var_name = malloc(250); // allocate arbitrary memory space
    int k = 0;
    while (i < temp_length && (is_letter(temp[i]) || is_digit(temp[i]) || temp[i] == '_')) // detect shell_variable name
        var_name[k++] = temp[i++];
    var_name[k] = '\0';
    var_name = realloc(var_name, k + 1); // reallocating the proper memory space
    return var_name;
}

int replace_var(char *argument, char *var_name, int j) {
    char *var_value = get_variable(var_name);
    if (var_value == NULL)
        var_value = get_environment_variable(var_name);
    free (var_name);
    if (var_value == NULL)
        return -1; // variable does not exist
    int length = strlen(var_value);
    for (int k = 0; k < length; k++) // append home path, ignoring the leading '/'
        argument[j++] = var_value[k];
    return j;
}

void handle_assignment(char *argument, char *temp, int temp_length, int j) {
    if (!check_var_name(argument)) {
        properties.error_message = "ERROR: INVALID VARIABLE NAME!";
        return;
    }
    add(arg_list, argument);
    char *value = malloc(temp_length - j);
    strncpy(value, &temp[j + 1], temp_length - j);
    value[strlen(value)] = '\0'; // could be removed
    add(arg_list, value);
    free(temp); // getting rid of the old-version argument
}

bool check_var_name(char *argument) {
    if (is_digit(argument[0]))
        return false;
    int length = strlen(argument);
    bool valid;
    for (int i = 0; i < length; ++i) {
        valid = is_letter(argument[i]) || is_digit(argument[i]) || argument[i] == '_';
        if (!valid)
            return false;
    }
    return true;
}

void reset() {
    properties.is_assignment = false;
    properties.is_in_background = false;
    properties.has_error = false;
    properties.error_message = NULL;
    if (arg_list != NULL)
        destroy_list(arg_list);
    arg_list = create_list();
}