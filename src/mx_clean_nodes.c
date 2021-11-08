#include "pathfinder.h"

void mx_clean_nodes(node_t **nodes) {
    for (int i = 0; nodes[i] != NULL; i++) {
        mx_del_node(&nodes[i]);
    }
    free(nodes);
    nodes = NULL;
}
