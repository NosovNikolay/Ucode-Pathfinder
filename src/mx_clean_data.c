#include "pathfinder.h"

void mx_clean_data(graph_info_t *data) {
    for (int i = 0; i < data->bridges_count; i++) {
        if (data->bridges[i]->left) free(data->bridges[i]->left);
        if (data->bridges[i]->right) free(data->bridges[i]->right);
        free(data->bridges[i]);
    }
    for (int i = 0; i < data->islands_count; i++) {
        free(data->islands[i]);
    }
    free(data->islands);
    free(data->bridges);
    free(data);
}
