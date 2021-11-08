#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int n = 0;   
    const char* temp = str;
    while ((temp = mx_strstr(temp, sub)) != 0) {
        n++;
        temp++;  
    }
    return n;
}
