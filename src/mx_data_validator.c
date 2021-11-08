#include "pathfinder.h"

static bool is_bridges_equal(bridge_t *a, bridge_t *b) {
    // A-B,11
    // A-B,11
    if (mx_strcmp(a->left, b->left) == 0   
        && mx_strcmp(a->right, b->right) == 0) {
            return true;
        }
    // A-B,11
    // B-A,11
    else if(mx_strcmp(a->left, b->right) == 0   
        && mx_strcmp(a->right, b->left) == 0) {
            return true;
    }
    return false;
}

static int how_many_islands(bridge_t **bridges, int size) {
    int length = 0;
    for (int i = 0; i < size; i++) {
        length += mx_strlen(bridges[i]->left);
        length += mx_strlen(bridges[i]->right);
    }

    char *islands = mx_strnew(length + 1);
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (!mx_strstr(islands, bridges[i]->left)) {
            mx_strcat(islands, bridges[i]->left);
            j++;
        }
        if (!mx_strstr(islands, bridges[i]->right)) {
            mx_strcat(islands, bridges[i]->right);
            j++;
        }
    }
    free(islands);
    return j;
}

static bool is_only_digit(const char *str) {
    for (char *i = (char *)str; *i != '\0'; i++) {
        if (!mx_isdigit(*i)) {
            return false;
        }
    }
    return true;
}

static bool is_valid_line(const char *str) {
    int i = 0;
    // skip first island
    while (mx_isalpha(str[i])) {
        i++;
    }
    // skip delimiter
    i++;
    // check 2-nd island
    while (str[i] != ',' && str[i] != '\0') {
        if (!mx_isalpha(str[i])) {
            return false;
        }
        i++;
    }
    // skip delim
    i++;
    while (i != mx_strlen(str)) {
        if (!mx_isdigit(str[i])) {
            return false;
        }
        i++;
    }
    return true;
}

graph_info_t *mx_data_validator(const char *filename) {
    graph_info_t *data = malloc(sizeof(graph_info_t));

    char *str = mx_file_to_str(filename);

    char **lines = mx_strsplit(str, '\n');
    // Count of islands format
    if (!is_only_digit(lines[0])) {
        mx_printerr("error: line 1 is not valid\n");
        free(str);
        mx_del_strarr(&lines);
        free(data);
        exit(1);
    }

    int size = 0;
    for (int i = 0; lines[i] != NULL; i++) size++;
    int offset = 0;
    for (int i = size - 1; mx_isspace(lines[i][0]) && i >= 0; i--) {
        offset++;
    }
    data->bridges_count = size - 1;
    lines[size - offset] = NULL;
    // Line validation
    // Name-Name,num
    for (int i = 1; i < size; i++) {
        if (!is_valid_line(lines[i])) {
            mx_printerr("error: line ");
            char *line_num = mx_itoa(i + 1);
            mx_printerr(line_num);
            mx_printerr(" is not valid\n");
            free(line_num);
            mx_del_strarr(&lines);
            free(str);
            free(data);
            exit(1);
        }
    }

    data->bridges = malloc(sizeof(bridge_t *) * data->bridges_count);
    for (int i = 0; i < data->bridges_count; i++) {
        data->bridges[i] = malloc(sizeof(bridge_t));
    }

    char **tmp;
    char **sec_tmp;
    int invalid_line = -1;

    for (int i = 0, j = 1; i < data->bridges_count; i++, j++) {
        int avariika = 0;
        tmp = mx_strsplit(lines[j], '-');
        for (int k = 0; tmp[k]; k++) {
            avariika++;
        }
        if (avariika > 2) {
            mx_del_strarr(&tmp);
            invalid_line += i + 2;
            break;
        }

        data->bridges[i]->left = tmp[0];
        sec_tmp = mx_strsplit(tmp[1], ',');
        data->bridges[i]->right = sec_tmp[0];
        data->bridges[i]->length = mx_atoi(sec_tmp[1]);
        free(sec_tmp[1]);
        free(sec_tmp);
        free(tmp[1]);
        free(tmp);
    }
    // If first line value isn't correct
    if (how_many_islands(data->bridges, data->bridges_count) !=
        mx_atoi(lines[0])) {
        mx_printerr("error: invalid number of islands\n");
        free(str);
        mx_del_strarr(&lines);
        for (int i = 0; i < data->bridges_count; i++) {
            if (data->bridges[i]->left) free(data->bridges[i]->left);
            if (data->bridges[i]->right) free(data->bridges[i]->right);
            free(data->bridges[i]);
        }
        free(data->bridges);
        free(data);
        exit(1);
    }
    // If the graph has loops 
    // For example A-A,10
    for (int i = 0; i < data->bridges_count; i++) {
        if (mx_strcmp(data->bridges[i]->left, data->bridges[i]->right) == 0) {
            mx_printerr("error: line ");
            char *line_num = mx_itoa(i + 2);
            mx_printerr(line_num);
            mx_printerr(" is not valid\n");
            free(line_num);
            free(str);
            mx_del_strarr(&lines);
            for (int i = 0; i < data->bridges_count; i++) {
                if (data->bridges[i]->left) free(data->bridges[i]->left);
                if (data->bridges[i]->right) free(data->bridges[i]->right);
                free(data->bridges[i]);
            }
            free(data->bridges);
            free(data);
            exit(1);
        }
    }
    // If the nodes has more than 1 link
    // A-B,10
    // A-B,12
    // Or
    // B-A,10
    // A-B,12
    for (int i = 0; i < data->bridges_count - 1; i++) {
        for (int j = i + 1; j < data->bridges_count; j++) {
            if (is_bridges_equal(data->bridges[i], data->bridges[j])) {
                mx_printerr("error: duplicate bridges\n");
                free(str);
                mx_del_strarr(&lines);
                for (int i = 0; i < data->bridges_count; i++) {
                    if (data->bridges[i]->left) free(data->bridges[i]->left);
                    if (data->bridges[i]->right) free(data->bridges[i]->right);
                    free(data->bridges[i]);
                }
                free(data->bridges);
                free(data);
                exit(1);
            }
        }
    }


    data->islands = malloc(
        sizeof(char *) * how_many_islands(data->bridges, data->bridges_count));
    data->islands_count = how_many_islands(data->bridges, data->bridges_count);

    for (int i = 0; i < data->islands_count; i++) {
        data->islands[i] = "";
    }

    int i = 0;
    for (int j = 0; j < data->bridges_count; j++) {
        if (!is_in_arr(data->islands, data->bridges[j]->left,
                       data->islands_count)) {
            data->islands[i] = mx_strdup(data->bridges[j]->left);
            i++;
        }
        if (!is_in_arr(data->islands, data->bridges[j]->right,
                       data->islands_count)) {
            data->islands[i] = mx_strdup(data->bridges[j]->right);
            i++;
        }
    }

    long long sum = 0;
    for (int i = 0; i < data->bridges_count; i++) {
        sum += data->bridges[i]->length;
    }
    // If we go beyond INT MAX
    if (sum > INT_MAX || sum < 0) {
        free(str);
        mx_del_strarr(&lines);
        mx_clean_data(data);
        mx_printerr("error: sum of bridges lengths is too big\n");
        exit(1);
    }

    free(str);
    mx_del_strarr(&lines);

    return data;
}
