#ifndef PRE_PARSER_H
#define PRE_PARSER_H

#define MAX_LENGTH 512

/*
 * returns:
 * (-1) if command length > MAX_LENGTH,
 *  (0) if command is comment or empty line,
 *  (1) otherwise
 */
int get_status(char *command, int length);

#endif
