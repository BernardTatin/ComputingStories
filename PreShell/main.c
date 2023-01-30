/*
 * main.c
 *
 * project: PreShell
 * author:  bernard
 * date:    2023 - 01 - 29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path-loader.h"

int main(int argc, char **argv) {
    int exit_value = EXIT_SUCCESS;
    char *path = NULL;
    for (int i = 1; i<argc; i++) {
        if (strcmp(argv[i], "--path") == 0) {
            i++;
            if (i == argc) {
                fprintf(stderr, "ERROR: --path argument needs a value. Bye...\n");
                exit(EXIT_FAILURE);
            } else {
                path = argv[i];
            }
        } else {
            fprintf(stderr, "Cannot do anything with this argument (%s), sorry\n", argv[i]);
        }
    }
    if (path == NULL) {
        path = getenv("PATH");
    }
    if (load_path(path)) {
        show_all_exe();
        delete_tree_path();
    } else {
        fprintf(stderr, "Cannot load the current path(%s)\n", path);
        exit_value = EXIT_FAILURE;
    }
    return exit_value;
}
