#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;

    unsigned char *ptr_to_sought = NULL;

    while ((s != NULL) && (n--)) {
        if (*p != (unsigned char)c) {
            p++;
        } else {
            ptr_to_sought = p;
            break;
        }
    }
    return ptr_to_sought;
}
