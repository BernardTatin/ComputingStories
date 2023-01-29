/*
 * path-loader.h
 *
 * project: PreShell
 * author:  bernard
 * date:    2023 - 01 - 29
 */


#ifndef PRESHELL_PATH_LOADER_H
#define PRESHELL_PATH_LOADER_H

#include <stdbool.h>

bool load_path(const char *path);
char *get_exe_path(const char *exe_name);
void show_all_exe(void);
bool control_tree_path(void);

#endif //PRESHELL_PATH_LOADER_H
