/*
 * path-loader.c
 *
 * project: PreShell
 * author:  bernard
 * date:    2023 - 01 - 29
 */

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "rb_tree.h"
#include "path-loader.h"

typedef struct {
    char *path;
    int count;
    int order;
} node_of_path;

static struct rb_tree *tree_path = NULL;

static int t_path_cmp(struct rb_tree *self,
                      struct rb_node *node_a,
                      struct rb_node *node_b) {
    node_of_path *a = (node_of_path *) node_a->value;
    node_of_path *b = (node_of_path *) node_b->value;
    return strcmp(a->path, b->path);
}

static inline node_of_path *create_path_node(char *new_path, const int order) {
    node_of_path *tp = (node_of_path *) calloc(1, sizeof(node_of_path));
    tp->path = new_path;
    tp->count = 1;
    tp->order = order;
    return tp;
}

static bool path_exists(const char *path) {
    DIR* dir = opendir(path);
    if (dir) {
        /* Directory exists. */
        closedir(dir);
        return true;
    } else {
        fprintf(stderr, "Directory %s cannot be accessed\n", path);
        return false;
    }
}

static bool add_to_tree_path(struct rb_tree *tree, char *new_path, const int order) {
    if (path_exists( new_path)) {
        node_of_path *tp    = create_path_node(new_path, order);
        node_of_path *found = rb_tree_find(tree, tp);
        if (found == NULL) {
            node_of_path *ti = create_path_node(new_path, order);
            rb_tree_insert(tree, ti);
            return true;
        } else {
            found->count += 1;
            return false;
        }
    } else {
        return false;
    }
}

static bool control_tree_path(void) {
    struct rb_iter *iterator = rb_iter_create();
    bool r = true;
    if (iterator != NULL) {
        for (node_of_path *v = rb_iter_first(iterator, tree_path);
             v;
             v = rb_iter_next(iterator)
                ) {
            if (v->count > 1) {
                fprintf(stdout,
                        "WARNING %s found %d times 1st occurrence at %d\n",
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
            if (add_to_tree_path(tree_path, strdup(token), order++)) {
                fprintf(stdout, "You can add the files from %s\n", token);
            }
        }
        free(path);
        control_tree_path();
        return true;
    } else {
        return false;
    }
}
char *get_exe_path(const char *exe_name) {
    return NULL;
}

void show_all_exe(void) {
    struct rb_iter *iterator = rb_iter_create();
    if (iterator != NULL) {
        for (node_of_path *v = rb_iter_first(iterator, tree_path);
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
