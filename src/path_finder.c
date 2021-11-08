#include "pathfinder.h"

bool is_in_arr(char **arr, char *str, int size) {
    if (*arr == NULL) return false;
    for (int i = 0; i < size; i++) {
        if (mx_strcmp(arr[i], str) == 0) {
            return true;
        }
    }
    return false;
}

void mx_del_node(node_t** node) {
    mx_strdel(&(*node)->name);
    for (int i = 0; i < (*node)->bridges_count; i++) free((*node)->bridges[i]);
    free((*node)->bridges);
    free(*node);
}

print_data_t *mx_create_path(const char* src) {
    print_data_t *path = malloc(sizeof(print_data_t));
    path->distances = malloc(sizeof(int) * 0);
    path->visited = malloc(sizeof(char*) * 1);
    path->visited[0] = mx_strdup(src);
    path->visited_count = 0;
    path->sum_distances = 0;
    return path;
}

void mx_add_visited(print_data_t* path, const char* name, int len) {
    path->distances =
        (int*)mx_realloc(path->distances, (path->visited_count + 1) * sizeof(int));
    path->visited = (char**)mx_realloc(path->visited,
                                    (path->visited_count + 2) * sizeof(char*));
    path->distances[path->visited_count] = len;
    path->visited[path->visited_count + 1] = mx_strdup(name);
    path->visited_count++;
    path->sum_distances += len;
}

print_data_t *mx_dup_path(print_data_t *src) {
    if (!src) {
        return NULL;
    }
    print_data_t *path = malloc(sizeof(print_data_t));
    path->visited_count = src->visited_count;
    path->sum_distances = src->sum_distances;
    path->distances = malloc(sizeof(int) * src->visited_count);
    for (int i = 0; i < src->visited_count; i++)
        path->distances[i] = src->distances[i];
    path->visited = (char**)malloc(sizeof(char*) * (src->visited_count + 1));
    for (int i = 0; i <= src->visited_count; i++)
        path->visited[i] = mx_strdup(src->visited[i]);
    return path;
}

void mx_del_path(print_data_t **path) {
    for (int i = 0; i <= (*path)->visited_count; i++)
        mx_strdel(&(*path)->visited[i]);
    free((*path)->visited);
    free((*path)->distances);
    (*path)->distances = NULL;
    free(*path);
    *path = NULL;
}

print_data_array *mx_create_path_arr() {
    print_data_array* path_arr = malloc(sizeof(print_data_array));
    path_arr->length = 0;
    path_arr->paths = malloc(sizeof(print_data_t*) * 0);
    return path_arr;
}

void mx_add_path(print_data_array* path_arr, print_data_t* path) {
    path_arr->paths = (print_data_t**)mx_realloc(
        path_arr->paths, (path_arr->length + 1) * sizeof(print_data_t*));
    path_arr->paths[path_arr->length] = path;
    path_arr->length++;
}

void mx_clean_path_arr(print_data_array* path_arr) {
    for (int i = 0; i < path_arr->length; i++)
        mx_del_path(&(path_arr->paths[i]));
    free(path_arr->paths);
    path_arr->paths = malloc(sizeof(print_data_t*) * 0);
    path_arr->length = 0;
}

void mx_del_path_arr(print_data_array** path_arr) {
    for (int i = 0; i < (*path_arr)->length; i++)
        mx_del_path(&(*path_arr)->paths[i]);
    free((*path_arr)->paths);
    free(*path_arr);
    *path_arr = NULL;
}

print_data_array *mx_find_path(node_t* begin, node_t* end, print_data_t* path,
                               int max_distance) {
    long min_len = INT_MAX;
    print_data_array *path_arr = mx_create_path_arr();
    print_data_t *cur_path = NULL;
    print_data_array *deep_path_arr = NULL;
    links_t *tmp_link = NULL;
    for (int i = 0; i < begin->bridges_count; i++) {
        tmp_link = begin->bridges[i];
        if (is_in_arr(path->visited, tmp_link->next->name, path->visited_count + 1)) {
            continue;
        }
        int len = path->sum_distances + tmp_link->lengh_to_next;
        if (len > min_len) {
            continue;
        }

        if (!mx_strcmp(tmp_link->next->name, end->name)) {
            if (len < min_len) {
                min_len = len;
                mx_clean_path_arr(path_arr);
            }
            if (len == min_len) {
                cur_path = mx_dup_path(path);
                mx_add_visited(cur_path, tmp_link->next->name,
                                  tmp_link->lengh_to_next);
                mx_add_path(path_arr, cur_path);
            }
            cur_path = NULL;
            continue;
        }

        if (path->visited_count >= max_distance) {
            continue;
        }
        cur_path = mx_dup_path(path);
        mx_add_visited(cur_path, tmp_link->next->name,
                          tmp_link->lengh_to_next);
        deep_path_arr = mx_find_path(tmp_link->next, end, cur_path, max_distance);
        for (int j = 0; j < deep_path_arr->length; j++) {
            print_data_t *tmp = deep_path_arr->paths[j];
            if (tmp->sum_distances < min_len) {
                min_len = tmp->sum_distances;
                mx_clean_path_arr(path_arr);
            }
            if (tmp->sum_distances == min_len) {
                mx_add_path(path_arr, tmp);
            } else {
                mx_del_path(&tmp);
            }
        }
        free(deep_path_arr->paths);
        free(deep_path_arr);
        mx_del_path(&cur_path);
    }
    return path_arr;
}
