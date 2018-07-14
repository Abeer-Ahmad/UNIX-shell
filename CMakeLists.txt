cmake_minimum_required(VERSION 3.8)
project(Lab_1___Shell_and_System_Calls)

set(CMAKE_C_STANDARD 99)

add_executable(Lab_1___Shell_and_System_Calls
        
        src/datastructures/linked_list.c
        src/datastructures/linked_list.h
        src/datastructures/string.c
        src/datastructures/string.h

        src/handlers/command/command_handler.c
        src/handlers/command/command_handler.h
        src/handlers/error/error_handler.c
        src/handlers/error/error_handler.h
        src/handlers/file/file_handler.c
        src/handlers/file/file_handler.h

        src/parser/command_parser.h
        src/parser/command_parser.c
        src/parser/pre_parser.c
        src/parser/pre_parser.h

        src/system/commands.c
        src/system/commands.h
        src/system/process.c
        src/system/process.h

        src/variables/environment.c
        src/variables/environment.h
        src/variables/shell_variables.c
        src/variables/shell_variables.h

        src/main.c)