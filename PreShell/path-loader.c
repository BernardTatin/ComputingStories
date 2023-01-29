/*
 * path-loader.c
 *
 * project: PreShell
 * author:  bernard
 * date:    2023 - 01 - 29
 */

#include <stdio.h>
#include "path-loader.h"

bool load_path(const char *path) {
    fprintf(stdout, "Loading from <%s>\n", path);
    return true;
}
char *get_exe_path(const char *exe_name) {
    return NULL;
}

void show_all_exe(void) {
    fprintf(stdout, "Nothing new here...\n");
}
