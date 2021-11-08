#include "pathfinder.h"

void clean_data(graph_info_t *data) {   
    if (data != NULL) {
        if (data->islands != NULL) {
            for (int i = 0; i < data->islands_count; i++) {
                if (data->islands[i] != NULL) {
                    free(data->islands[i]);
                }
            }
            free(data->islands);
        }
        if (data->bridges != NULL) {
            for (int i = 0; i < data->bridges_count; i++) {
                if (data->bridges[i] != NULL) {
                    if (data->bridges[i]->right != NULL) {
                        free(data->bridges[i]->right);
                    }
                    if (data->bridges[i]->left != NULL) {
                        free(data->bridges[i]->left);
                    }
                    free(data->bridges[i]);
                }
            }
            free(data->bridges);
        }
        free(data);
    }    
}

bool mx_isonlydigit(const char *str) {
    for (char *i = (char *)str; *i != '\0'; i++)
        if (!mx_isdigit(*i)) return false;
    return true;
}

// //need to fix
// static void check_islands_count(char **str_arr, int count) {
//     int i = 0;
//     while (str_arr[i] != NULL) {
//         i++;
//     }
//     if (count != i - 1) {
//         mx_printerr("error: invalid number of islands");
//         exit(1);
//     }
// }
// #include <stdio.h>
// static void check_islands(char **str_arr) {
//     char **tmp = NULL;
//     char delim = '-';
//     int j = 0;

//     for (int i = 1; str_arr[i]; i++) {
//        // printf ("%s   ", str_arr[i]);
//         tmp = mx_strsplit(str_arr[i], ',');
//        // printf( "\n%s ", tmp[0]);
//         // if (mx_strstr(tmp[i], "-")) {
//         //     mx_printerr("inv");
//         //     exit(1);
//         // }
//         while (tmp[0][j]) {
//             if (tmp[0][j] == delim) break;
//             if (!mx_isalpha(tmp[0][j])) {
//                 mx_printerr("nebukva");
//                 exit(1);
//             }
//             j++;
//         }
//        // printf("%c", tmp[0][j]);
//         j++;
//         while (tmp[0][j]) {
//             if (!mx_isalpha(tmp[0][j])) {
//                 mx_printerr("nebukva2");
//                 exit(1);
//             }
//             j++;
//         }
//         j = 0;
//         check_dublicates(tmp[0]);
//     }
// }

// void mx_data_validator(const char *filename) {
//     int count = check_first_line(filename);
//     count++;
//     char *data = mx_file_to_str(filename);
//     char **str_arr = mx_strsplit(data, '\n');
//     check_islands_count(str_arr, count);
//     check_islands(str_arr);
// }

int is_in_array(char **array, char *str) {
    for (int i = 0; array[i]; i++) {
        if (mx_strcmp(array[i], str) == 0) {
            return i;
        }
    }
    return -1;
}
// Ne raboatet
graph_info_t *pf_parse(char *filename, bool *is_valid) {
    // Open file
    char *str = mx_file_to_str(filename);

    char **lines = mx_strsplit(str, '\n');
    
    // for(int i = 0; lines[i]; i++) {
    //     // if (mx_strcmp(lines[i], "\n")) {
    //     //     free(lines[i]);
    //     //     lines[i] = NULL;
    //     // }
    // }
    // int size = 0;
    // for (int i = 0; lines[i] != NULL; i++) size++;
    // int offset = 0;
    // for (int i = size - 1; mx_isspace(lines[i][0]) && i >= 0; i--) {
    //     free(lines[size - offset]);
    //     lines[size - offset] = NULL;
    //     offset++;
    // }
    // free(lines[size - offset]);
    // lines[size - offset] = NULL;

    // First line
    if (!mx_isonlydigit(lines[0])) {
        mx_printerr("error: line 1 is not valid\n");
        mx_del_strarr(&lines);
        free(str);
        *is_valid = false;
        return NULL;
    }
    int first_line = mx_atoi(lines[0]);

    // Bridge count
    int bridge_count = 0;
    for (int i = 1; lines[i] != NULL; i++) bridge_count++;

    // graph_info_t init
    graph_info_t *data = malloc(sizeof(graph_info_t));
    data->islands = malloc(sizeof(char *) * 5);
    data->bridges = malloc(sizeof(bridge_t *) * bridge_count);
    for (int i = 0; i < bridge_count; i++)
        data->bridges[i] = malloc(sizeof(bridge_t*));
    data->bridges_count = bridge_count;
    data->islands_count = 5;
    first_line++;
    mx_del_strarr(&lines);
    free(str);
    return data;
}
