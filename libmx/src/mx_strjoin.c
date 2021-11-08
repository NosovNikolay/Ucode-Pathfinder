#include "libmx.h"
char *mx_strjoin(char const *s1, char const *s2) {
    char *str = NULL;

    if (!s1 && !s2)
        return NULL;
    
    else if (!s1) 
        return mx_strdup(s2);
    
    else if (!s2) 
        return mx_strdup(s1);

    if (!(str = mx_strnew(mx_strlen(s1) + mx_strlen(s2)))) 
        return NULL;

    str = mx_strcat((char*)s1, s2);

    return str;
}

