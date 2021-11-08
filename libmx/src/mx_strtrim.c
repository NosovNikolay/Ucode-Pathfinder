#include "libmx.h"
//need to fix
static int space_b(char *str) {
    int i = 0;
    while (mx_isspace(str[i]) && i != mx_strlen(str))
        i++;
    return i;
}

static int space_a(char *str) {
    int i = mx_strlen(str) - 1;
    while (mx_isspace(str[i]) && i > 0) 
        i--;
    return i;
}

char *mx_strtrim(const char *str) {
    char *result = NULL;    
    int start = 0;
    int end = 0;
    int j = 0;
    if (!str)
        return NULL;

    start = space_b((char*)str);
    end = space_a((char*)str);
    result = mx_strnew(-start + end);

    if (result == NULL)
        return NULL;

    for (int i = start; i < end + 1; i++) {
        result[j] = str[i];
        j++;
    }
    result[j] = '\0';
    return result;
}

