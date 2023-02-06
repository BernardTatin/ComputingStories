/*
 * private_rb_tree.h
 *
 * project: optimize_rbtree
 * author:  bernard
 * date:    2023 - 02 - 03
 */


#ifndef OPTIMIZE_RBTREE_PRIVATE_RB_TREE_H
#define OPTIMIZE_RBTREE_PRIVATE_RB_TREE_H

typedef struct rb_node {
    int      red;     // Color red (1), black (0)
    rb_node *link[2]; // Link left [0] and right [1]
    rb_data *data;   // User provided, used indirectly via rb_tree_node_cmp_f.
}            rb_node;

typedef struct rb_tree {
    rb_node            *root;
    rb_tree_node_cmp_f cmp_node;
    rb_tree_node_free  free_node;
    size_t             size;
}            rb_tree;

typedef struct rb_iter {
    struct rb_tree *tree;
    struct rb_node *node;                     // Current node
    struct rb_node *path[RB_ITER_MAX_HEIGHT]; // Traversal path
    size_t         top;                      // Top of stack
}            rb_iter;

static inline rb_node *rb_node_init(rb_node *self, rb_data *value) {
    if (self) {
        self->red = 1;
        self->link[0] = self->link[1] = NULL;
        self->data = value;
    }
    return self;
}

static inline rb_node *rb_node_alloc() {
    return rb_malloc(sizeof(rb_node));
}

static inline
void rb_node_dealloc(rb_node *self) {
    if (self) {
        free(self);
    }
}

#endif //OPTIMIZE_RBTREE_PRIVATE_RB_TREE_H
