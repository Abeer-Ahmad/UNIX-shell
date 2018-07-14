#include <stdbool.h>
#include "string.h"

bool is_letter(char ch) {
    return (ch >= 'A' &&  ch <= 'Z') || (ch >= 'a' &&  ch <= 'z');
}

bool is_digit(char ch) {
    return (ch >= '0' &&  ch <= '9');
}

bool is_space(char ch) {
    return (ch == SPACE || ch == TAB);
}
