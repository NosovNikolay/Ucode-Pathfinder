#include "pathfinder.h"

// Parse to adjacency matrix
// Used for Floyd and Dijktras algorithm
int get_element_index(char **arr, char *element) {
    for (int i = 0; arr[i] != NULL; i++) {
        if (mx_strcmp(arr[i], element) == 0) {
            return i;
        }
    }
    return -1;
}

void fill_array(int **arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = 999;
        }
    }
    for (int i = 0; i < size; i++) {
        int j = i;
        arr[i][j] = 0;
    }
}

int **create_array(int w, int l) {
    int **arr = malloc(w * sizeof(int *));

    for (int k = 0; k < l; k++) {
        arr[k] = malloc(l * sizeof(int));
    }

    return arr;
}

void copy_arr(int **src, int **dst, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

#include <stdio.h>
int **parse_to_arr(graph_info_t *data) {
    int **arr = create_array(data->islands_count, data->islands_count);

    fill_array(arr, data->islands_count);

    for (int i = 0; i < data->bridges_count; i++) {
        int k = get_element_index(data->islands, data->bridges[i]->left);
        int j = get_element_index(data->islands, data->bridges[i]->right);
        arr[k][j] = data->bridges[i]->length;
        arr[j][k] = data->bridges[i]->length;
    }

    // for (int i = 0; i < data->islands_count; i++) {
    //     for (int j = 0; j < data->islands_count; j++) {
    //         printf("%d\t", arr[i][j]);
    //     }
    //     printf("\n");
    // }

    return arr;
}
// 0 11 10 999 999
// 11 1 999 5 999
// 10 999 2 6 15
// 999 5 6 3 4
// 999 999 15 4 0
