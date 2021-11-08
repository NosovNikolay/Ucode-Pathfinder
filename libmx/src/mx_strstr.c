#include "libmx.h"

char *mx_strstr(const char *s1, const char *s2) {
    int size = 0;
    size = mx_strlen(s2);
    while(*s1) {
        if(!mx_strncmp(s1, s2, size)) {
            return (char*)s1;  
        }
        s1++;
    }
    return NULL;
}
