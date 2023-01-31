/*
 * main.c
 * Project: optimize-rbtree
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "rb_tree.h"

const int line_length = 511;

typedef struct {
    char *word;
    int count;
} sword;

static sword *new_sword(const char *word) {
    sword *s = rb_malloc(sizeof(sword));
    s->word = strdup(word);
    s->count = 1;
    return s;
}

static int cmp_sword(rb_node *na, rb_node *nb) {
    sword *a = (sword *)na->value;
    sword *b = (sword *)nb->value;
    return strcmp(a->word, b->word);
}

static inline rb_tree *get_tree() {
    rb_tree *tree = rb_tree_create(cmp_sword);
    return tree;
}

static bool load(rb_tree *tree, const char *file_name) {
    if (tree != NULL) {
        FILE *f = fopen(file_name, "r");
        if (f != NULL) {
            char line[line_length + 1];
            while(fgets(line, line_length, f) != NULL) {
                int l = strlen(line);
                if (l>0) {
                    line[l-1] = 0;
                }
                sword *s = new_sword(line);
                sword *found = rb_tree_find(tree, s);
                if (found == NULL) {
                    rb_tree_insert(tree, s);
                } else {
                    found->count +=1;
                }
            }
            return true;
        } else {
            return false;
        }
    } else {
        fprintf(stderr, "ERROR: Cannot create tree\n");
        return false;
    }
}

static void write(rb_tree *tree) {
    struct rb_iter *iter = rb_iter_create();
    if (iter) {
        for (sword *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)) {
            fprintf(stdout, "%7d %s\n", v->count, v->word);
        }
    }
}

static void dealloc_tree_node(rb_tree  *self, rb_node *node) {
    sword *nop = node->value;
    if (nop != NULL) {
        if (nop->word != NULL) {
            free(nop->word);
        }
    }
}

static void delete_tree(rb_tree *tree) {
    rb_tree_dealloc(tree, dealloc_tree_node);
}

int main(int argc, char **argv) {
    for (int i=1; i<argc; i++) {
        rb_tree *tree = get_tree();
        if (load(tree, argv[i])) {
            write(tree);
        }
        delete_tree(tree);
    }
    return 0;
}
