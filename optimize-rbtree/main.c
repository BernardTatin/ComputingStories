/*
 * main.c
 * Project: optimize-rbtree
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "rb_tree.h"

#define STATIC

const int line_length = 511;

typedef struct {
    char *word;
    int *count;
} sword;


STATIC sword *new_sword(const char *word) {
    sword *s = rb_malloc(sizeof(sword));

    s->word = strdup(word);
    s->count = (int *)malloc(sizeof(int));
    *s->count = 1;
    return s;
}

STATIC int cmp_sword(rb_key_ptr na, rb_key_ptr nb) {
    if (na == nb) {
        return 0;
    } else {
        char *a = (char *) na;
        char *b = (char *) nb;
        return strcmp(a, b);
    }
}

STATIC void free_sword(rb_node *node) {
    sword *nop = (sword *) rb_get_data(node);

    if (nop != NULL) {
        if (nop->word != NULL) {
            free(nop->word);
            free(nop->count);
        }
        free(nop);
    }
}

STATIC rb_tree *get_tree() {
    rb_tree *tree = rb_tree_create(cmp_sword, free_sword);
    return tree;
}

STATIC bool load(rb_tree *tree, const char *file_name) {
    if (tree != NULL) {
        FILE *f = fopen(file_name, "r");
        if (f != NULL) {
            char line[line_length + 1];
            while(fgets(line, line_length, f) != NULL) {
                size_t l = strlen(line);
                if (l != 0) {
                    line[l-1] = 0;
                }
                // ======================================================================
                // note for me
                // please: DO NOT REMOVE the #if 1
                // ======================================================================
#if 1
                // more efficient code
                sword *found = (sword *)rb_tree_find(tree, line);
                if (found == NULL) {
                    sword *s = new_sword(line);
                    rb_tree_insert(tree, (rb_data *)s);
                } else {
                    *found->count +=1;
                }
#else
                // less efficient code with memory leaks
                // if the data is freed, the node itself is not freed
                // so, don't do that unless you fix the bug
                sword *s = new_sword(line);
                rb_node *found = rb_tree_insert(tree, s);
                if (found) {
                    sword *f = (sword *)found->data;
                    f->count++;
                    free(s->word);
                    free(s);
                }
#endif
            }
            fclose(f);
            return true;
        } else {
            return false;
        }
    } else {
        fprintf(stderr, "ERROR: Cannot create tree\n");
        return false;
    }
}

STATIC void write(rb_tree *tree) {
    struct rb_iter *iter = rb_iter_create();
    if (iter) {
        for (sword *v = (sword *)rb_iter_first(iter, tree); v; v = (sword *)rb_iter_next(iter)) {
            fprintf(stdout, "%7d %s\n", *v->count, v->word);
        }
        rb_iter_dealloc(iter);
    }
}

int main(int argc, char **argv) {
    for (int i=1; i<argc; i++) {
        rb_tree *tree = get_tree();
        if (load(tree, argv[i])) {
            write(tree);
        }
        rb_tree_dealloc(tree);
    }
    return 0;
}
