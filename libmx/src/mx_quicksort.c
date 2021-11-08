#include "libmx.h"

int mx_quicksort(char **arr, int begin, int end) {
    if (!arr || begin < 0 || end < 0) {
        return -1;
    }
    unsigned int swaps = 0;
    unsigned int middle = mx_strlen(arr[(begin + end) / 2]);
    char *tmp;
    unsigned int l = (unsigned int)begin;
    unsigned int r = (unsigned int)end;
    while (l <= r) {
        while ((unsigned int)mx_strlen(arr[l]) < middle) {
            l++;
        }
        while ((unsigned int)mx_strlen(arr[r]) > middle) {
            r--;
        }
        if (l > r) {
            continue;
        }
        if (mx_strlen(arr[l]) != mx_strlen(arr[r])) {
            tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
            swaps++;
        }
        l++;
        r--;
    }
    if (r > (unsigned int)begin) {
        swaps += mx_quicksort(arr, begin, r);
    }
    if (l < (unsigned int)end) {
        swaps += mx_quicksort(arr, l, end);
    }
    return swaps;
}

