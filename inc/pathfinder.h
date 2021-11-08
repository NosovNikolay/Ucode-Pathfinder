#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

#define INT_MAX 2147483647

// Structs for validation and parse to matrix
typedef struct bridge_s {
	char *left;
	char *right;
	int length;
}		bridge_t;

typedef struct s_graph_info { 
	int islands_count;
	int bridges_count;
	char **islands;
	bridge_t **bridges;
}	graph_info_t;

// Structs for pathfinder
typedef struct s_graph_node node_t;

typedef struct links_s {
	int lengh_to_next;
	node_t *next;
}		links_t;

struct s_graph_node {
	char *name;
    links_t **bridges;
    int bridges_count;
    int index;
	bool is_visited;
};

// Structs for printing result
typedef struct print_data_s {
	char** visited;
	int visited_count;
    int *distances;
    int sum_distances;
}			print_data_t;

typedef struct s_print_data_array {
	print_data_t **paths;
	int length;
}			print_data_array;

// Validation

void mx_file_validator(int argc, char **argv);

graph_info_t *mx_data_validator(const char *filename);

// Print to console 

void mx_get_result(node_t **nodes, int size);

void mx_print_path(print_data_t *p);

// Parsing

node_t **mx_parse_to_nodes(graph_info_t *data);

int **parse_to_arr(graph_info_t *data);

// Clean data

void mx_clean_nodes(node_t **nodes);

void mx_clean_data(graph_info_t *data);

// Path finding 

print_data_array *mx_find_path(node_t *begin, node_t *end, print_data_t *path,
                        int max_distance);

// Utils

int **create_array(int w, int l);

void copy_arr(int **src, int **dst, int size);

node_t *mx_find_node_by_name(node_t** nodes, const char* name);

//void path_finder(int **matrix, int start, int islands_count, print_data_t *data);

node_t *mx_create_node_t(const char *name, int index);

bool is_in_arr(char **arr, char *str, int size);

void mx_add_link(node_t *node, links_t *link);

links_t *mx_create_bridge(int len, node_t* is);

void mx_add_new_link(node_t *a, node_t *b, int length);

//bool is_eq_islands(node_t* a, node_t* b);

void mx_del_node(node_t **node);

print_data_t *mx_create_path(const char* src);

void mx_add_path_point(print_data_t* path, const char* name, int len);

print_data_t *mx_dup_path(print_data_t* src);

void mx_del_path(print_data_t** path);

print_data_array *mx_create_path_arr();

void mx_add_path(print_data_array *path_arr, print_data_t *path);

void mx_clean_path_arr(print_data_array *path_arr);

void mx_del_path_arr(print_data_array **path_arr);

#endif
