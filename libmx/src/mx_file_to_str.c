#include "libmx.h"
//done
static int filesize(const char *fname) {
    if (!mx_strlen(fname)) return -1;
    int size = 0;
    int fn = open(fname, O_RDONLY);
    if (fn == -1) return -1;
    char buff[1];
    while (read(fn, buff, 1)) size++;
    close(fn);
    return size;
}

char *mx_file_to_str(const char *filename) {
    if (!filename) return NULL;
    int size = filesize(filename);
    if (size < 0) return NULL;
    int fn = open(filename, O_RDONLY);
    if (fn == -1) {
        return NULL;
    }
    char *text = (char *)malloc(size + 1);
    text[size] = '\0';
    read(fn, text, size);
    close(fn);
    return text;
}
