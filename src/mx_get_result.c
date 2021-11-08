#include "pathfinder.h"

void mx_get_result(node_t **nodes, int size) {
    print_data_t *path  = NULL;
    print_data_array *paths = NULL;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            path = mx_create_path(nodes[i]->name);
            paths = mx_find_path(
                nodes[i], nodes[j], path, size);
            for (int k = 0; k < paths->length; k++) {
                mx_print_path(paths->paths[k]);
            }
            mx_del_path(&path);
            mx_del_path_arr(&paths);
        }
    }
}
