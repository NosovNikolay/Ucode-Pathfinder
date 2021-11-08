#include "libmx.h"
//need to fix
char* mx_del_extra_spaces(const char* str) {
    if (!str) return NULL;
    char* trimmed = mx_strtrim(str);
    int pointer = 0;
    int current = 0;
    while (trimmed[pointer]) {
        trimmed[current++] = trimmed[pointer++];
        if (!mx_isspace(trimmed[pointer])) continue;
        while (mx_isspace(trimmed[pointer])) pointer++;
        trimmed[current++] = ' ';
    }
    trimmed[current] = '\0';
    char* result = mx_strncpy(mx_strnew(current), trimmed, current);
    mx_strdel(&trimmed);
    return result;
}
