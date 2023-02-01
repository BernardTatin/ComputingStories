/*
 * path-loader.c
 *
 * project: PreShell
 * author:  bernard
 * date:    2023 - 01 - 29
 */

#include <stdio.h>
#include <string.h>

#include "rb_tree.h"
#include "path-loader.h"
#include "tree-path.h"
#include "tree-bin.h"

/*
 * this tree is not the best way to work here,
 * the main aim is learning how to use the rb_tree API
 */
static rb_tree *tree_path = NULL;

bool control_tree_path(void) {
    rb_iter *iterator = rb_iter_create();
    bool r = true;
    if (iterator != NULL) {
        for (NodeOfPath *v = rb_iter_first(iterator, tree_path);
             v;
             v = rb_iter_next(iterator)
                ) {
            if (v->count > 1) {
                fprintf(stderr,
                        "WARNING: %s found %d times 1st occurrence at %d\n",
                        v->path, v->count, v->order);
                r = false;
            }
        }
        rb_iter_dealloc(iterator);
    } else {
        fprintf(stdout, "Cannot travel through the PATH\n");
        r = false;
    }
    return r;
}

bool load_path(const char *in_path) {
    char *path = strdup(in_path);
    char *token;
    char *rest = path;
    int order = 1;

    tree_path = rb_tree_create(t_path_cmp);
    if (tree_path != NULL) {
        while ((token = strtok_r(rest, ":", &rest)) != NULL) {
            switch  (add_to_tree_path(tree_path, token, order++)) {
                case DIR_OK:
                    fprintf(stdout, "You can add the files from %s\n", token);
                    explore_dir(token);
                    break;
                case DIR_NOT_FOUND:
                    fprintf(stderr,
                            "WARNING: Directory %s cannot be accessed\n",
                            token);
                    break;
                case DIR_ALREADY_USED:
                    fprintf(stderr, "WARNING: Directory %s already processed\n", token);
                    break;
            }
        }
        free(path);
        return true;
    } else {
        return false;
    }
}
char *get_exe_path(const char *exe_name) {
    return NULL;
}

void show_all_exe(void) {
    rb_iter *iterator = rb_iter_create();
    if (iterator != NULL) {
        for (NodeOfPath *v = rb_iter_first(iterator, tree_path);
             v;
             v = rb_iter_next(iterator)
                ) {
            fprintf(stdout,
                    "--> %2d %2d %s\n",
                    v->count,
                    v->order,
                    v->path);
        }
        rb_iter_dealloc(iterator);
    } else {
        fprintf(stdout, "Cannot travel through the PATH\n");
    }
}

static void dealloc_tree_node(rb_node *node) {
    NodeOfPath *nop = node->value;
    if (nop != NULL) {
        if (nop->path != NULL) {
            fprintf(stdout, "DEBUG: freeing %s\n", nop->path);
            free(nop->path);
        }
        free(nop);
    }
}

void delete_tree_path(void) {
    rb_tree_dealloc(tree_path, dealloc_tree_node);
    tree_path = NULL;
}
