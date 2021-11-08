#include "pathfinder.h"

int main(int argc, char **argv) {
    
    mx_file_validator(argc, argv);

    graph_info_t *data = mx_data_validator(argv[1]);

    node_t **nodes = mx_parse_to_nodes(data);

    mx_get_result(nodes, data->islands_count);

    mx_clean_nodes(nodes);

    mx_clean_data(data);
}
