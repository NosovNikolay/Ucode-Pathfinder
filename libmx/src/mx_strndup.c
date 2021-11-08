#include "libmx.h"
char* mx_strndup(const char* s1, size_t n) {
    if (!s1) {
        return NULL;
    }
    size_t len = (size_t)mx_strlen(s1);
    if (n < len) {
        len = n;
    }
    char* dup = mx_strnew(len);
    mx_strncpy(dup, s1, len);
    return dup;
}
