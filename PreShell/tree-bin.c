/*
 * tree-bin.c
 *
 * project: PreShell
 * author:  bernard
 * date:    2023 - 01 - 29
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "tree-bin.h"
#include "rb_tree.h"

typedef struct {
    char *name;
    char *path;
    int count;
} NodeOfBin;

static int t_bin_cmp(rb_node *na, rb_node *nb) {
    if (na == nb) {
        return 0;
    } else {
        NodeOfBin *a = (NodeOfBin *)na->value;
        NodeOfBin *b = (NodeOfBin *)nb->value;
        return strcmp(a, b);
    }
}
bool explore_dir(const char *dir_name) {
    struct dirent *pDirent;
    DIR *pDir;

    if ((pDir = opendir(dir_name)) != NULL) {
        while ((pDirent = readdir(pDir)) != NULL) {
            fprintf(stdout, "%s\n", pDirent->d_name);
        }
        closedir(pDir);
        return true;
    } else {
        return false;
    }
}
