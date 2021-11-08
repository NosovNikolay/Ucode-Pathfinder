#include "pathfinder.h"

void mx_file_validator(int argc, char **argv) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(1);
    }
    int state = open(argv[1], O_RDONLY);

    if (state == -1) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        close(state);
        exit(1);
    }

    char *str = mx_file_to_str(argv[1]);

    if(mx_strlen(str) == 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        free(str);
        close(state);
        exit(1);
    }
    close(state);
    free(str);
}
