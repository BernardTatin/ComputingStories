/*
 * tree-bin.h
 *
 * project: PreShell
 * author:  bernard
 * date:    2023 - 01 - 29
 */


#ifndef PRESHELL_TREE_BIN_H
#define PRESHELL_TREE_BIN_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    char *binary_name;
    char *main_path;
    int count;
} NodeOfBinary;

static inline bool is_binary_x(const char *path_name) {
    if (access(path_name, X_OK) == 0) {
        return true;
    } else {
        return false;
    }
}

bool explore_dir(const char *dir_name);

#endif //PRESHELL_TREE_BIN_H
