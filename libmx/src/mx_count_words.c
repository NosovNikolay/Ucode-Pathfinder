#include "libmx.h"
//poficsil
int mx_count_words(const char *str, char delimiter) {
    
    if (!str) {
        return -1;
    }
    int i = 0;
    int j = 0;
    
    if(str[i] == '\0') {
        return 0;
    }

    for(; str[i] != '\0'; i++) {
        if (str[i] == delimiter) {
            j++;
            while (str[i + 1] == delimiter) {
                i++;
            }
        }
    }

    str[0] == delimiter ? 0 : j++;
    str[i - 1] == delimiter ? j-- : 0;
    
    return j;
}
