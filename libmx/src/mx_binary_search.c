#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int start = 0;
    int end = size - 1;
    int mid = 0;

    while (start <= end) {
        
        mid = (start + end) / 2;
        *count = *count + 1;

        if(!mx_strcmp(arr[mid], s))    
            return mid;
        
        else if (mx_strcmp(s, arr[mid]) > 0)    
            start = mid + 1;
        
        else    
            end = mid - 1;
    }
    *count = 0;
    return -1;
}


