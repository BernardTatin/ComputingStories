/*
 * tree-path.h
 *
 * project: PreShell
 * author:  bernard
 * date:    2023 - 01 - 29
 *
 * NOTE: it's not the best way to manage this code
 * TODO: Clean me!
 */


#ifndef PRESHELL_TREE_PATH_H
#define PRESHELL_TREE_PATH_H

#include <dirent.h>

typedef struct {
    char *path;
    int count;
    int order;
} NodeOfPath;

typedef enum {
    DIR_OK,
    DIR_ALREADY_USED,
    DIR_NOT_FOUND
} DirState;

// DO NOT inline ! we need a pointer on it!
static int t_path_cmp(struct rb_tree *self,
                      struct rb_node *node_a,
                      struct rb_node *node_b) {
    NodeOfPath *a = (NodeOfPath *) node_a->value;
    NodeOfPath *b = (NodeOfPath *) node_b->value;
    return strcmp(a->path, b->path);
}

static inline NodeOfPath *create_path_node(char *new_path, const int order) {
    NodeOfPath *tp = (NodeOfPath *) calloc(1, sizeof(NodeOfPath));

    tp->path = new_path;
    tp->count = 1;
    tp->order = order;
    return tp;
}

static inline bool path_exists(const char *path) {
    DIR* dir = opendir(path);

    if (dir) {
        /* Directory exists. */
        closedir(dir);
        return true;
    } else {
        return false;
    }
}

static DirState add_to_tree_path(struct rb_tree *tree, char *new_path, const int order) {
    if (path_exists( new_path)) {
        NodeOfPath *tp    = create_path_node(new_path, order);
        NodeOfPath *found = rb_tree_find(tree, tp);

        if (found == NULL) {
            rb_tree_insert(tree, tp);
            return DIR_OK;
        } else {
            found->count += 1;
            return DIR_ALREADY_USED;
        }
    } else {
        return DIR_NOT_FOUND;
    }
}

#endif //PRESHELL_TREE_PATH_H
