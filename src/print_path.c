#include "pathfinder.h"

void mx_print_delim() {
    mx_printstr("========================================\n");
}

void mx_print_path(print_data_t *path) {
    mx_print_delim();
    mx_printstr("Path: ");
    mx_printstr(path->visited[0]);
    mx_printstr(" -> ");
    mx_printstr(path->visited[path->visited_count]);
    mx_printchar('\n');   
    mx_printstr("Route: ");
    
    // print route
    for (int i = 0; i < path->visited_count + 1; i++) {
        if (i != 0) {
            mx_printstr(" -> ");
        } 
        mx_printstr(path->visited[i]);
    }
    mx_printchar('\n');
    // print sum of steps
    mx_printstr("Distance: ");
    int size = 0;
    int last = path->visited_count - 1;
    if (path->visited_count > 1) {
        for (int i = 0; i < path->visited_count; i++) {
            if (i > 0) {
                mx_printstr(" + ");
            }
            mx_printint(path->distances[i]);
            size += path->distances[i];
            if (i == last) {
                mx_printstr(" = ");
            }
        }
    }
    else {
       size += path->distances[0]; 
    }
    mx_printint(size);
    mx_printchar('\n');
    mx_print_delim();
}
