#include <stdio.h>
#include <memory.h>
#include "command_handler.h"
#include "../../parser/command_parser.h"
#include "../../variables/shell_variables.h"
#include "../../system/commands.h"
#include "../../system/process.h"
#include "../../parser/pre_parser.h"
#include "../error/error_handler.h"
#include "../file/file_handler.h"
#include "../../variables/environment.h"

void handle_command(char *command) {
    int length = strlen(command); // pass to parsers
    int status = get_status(command, length);
    if (status == -1)
        print_error_message("ERROR: VERY LONG COMMAND!");
    else if (status == 0)
        return;
    else {
        update_history(command);
        char **args = parse(command);
        Properties properties = get_properties();
        if (properties.has_error) {
            print_error_message(properties.error_message);
        } else if (properties.is_assignment) {
            int i = !strcmp(args[0], "export");
            set_variable(args[i], args[i + 1]);
        } else if (!strcmp(args[0], "cd")) {
            cd (args[1]);
        } else if (!strcmp(args[0], "history")) {
            history ();
        } else {
            execute(args, properties.is_in_background);
        }
    }
}

void update_history(char *command) {
    FILE *history = get_file(get_history_path(), "a");
    write_to_file(history, command);
    close_file(history);
}