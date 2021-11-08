#include "pathfinder.h"

void mx_add_link(node_t *node, links_t *link) {
    node->bridges = mx_realloc(
        node->bridges, sizeof(links_t*) * (node->bridges_count + 1));
    node->bridges[node->bridges_count] = link;
    node->bridges_count++;
}

void mx_add_new_link(node_t *a, node_t *b, int length) {
    links_t *new = malloc(sizeof(links_t));
    new->lengh_to_next = length;
    new->next = b;
    mx_add_link(a, new);
}

node_t *mx_create_node_t(const char *name, int index) {
    node_t *node = malloc(sizeof(node_t));
    node->name = mx_strdup(name);
    node->bridges = malloc(sizeof(links_t*));
    node->bridges_count = 0;
    node->index = index;
    return node;
}

node_t *mx_find_node_by_name(node_t** nodes, const char* name) {
    for (int i = 0; nodes[i]; i++) {
        if (!mx_strcmp(nodes[i]->name, name)) {
            return nodes[i];
        }
    }
    return NULL;
}

node_t **mx_parse_to_nodes(graph_info_t* data) {
    node_t **nodes =
        (node_t**)malloc(sizeof(node_t*) * (data->islands_count + 1));
    for (int i = 0; i <= data->islands_count; i++) nodes[i] = NULL;

    for (int i = 0; i < data->islands_count; i++) {
        nodes[i] = mx_create_node_t(data->islands[i], i);
    }

    for (int j = 0; j < data->islands_count; j++) {
        for (int i = 0; i < data->bridges_count; i++) {
            if (mx_strcmp(nodes[j]->name, data->bridges[i]->left) == 0) {
                mx_add_new_link(
                    nodes[j], mx_find_node_by_name(nodes, data->bridges[i]->right),
                    data->bridges[i]->length);
            } else if (mx_strcmp(nodes[j]->name, 
                        data->bridges[i]->right) == 0) {
                mx_add_new_link(
                    nodes[j], mx_find_node_by_name(nodes, data->bridges[i]->left),
                    data->bridges[i]->length);
            }
        }
    }

    return nodes;
}
