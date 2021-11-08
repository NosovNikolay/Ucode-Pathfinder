#include "libmx.h"

char *mx_strdup(const char *str) {
    if(!str) {
        return NULL;
    }
    char *dup = NULL;
    
    dup = mx_strnew(mx_strlen(str));

    if (dup != NULL) {
        mx_strcpy(dup, str);
    }
    return dup;
}



