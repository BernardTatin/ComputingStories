/*
 * tree-bin.c
 *
 * project: PreShell
 * author:  bernard
 * date:    2023 - 01 - 29
 */

#include <stdio.h>
#include <dirent.h>

#include "tree-bin.h"

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
