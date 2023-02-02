//
// Based on Julienne Walker's <http://eternallyconfuzzled.com/> rb_tree
// implementation.
//
// Modified by Mirek Rusin <http://github.com/mirek/rb_tree>.
//
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
//

#ifndef __RB_TREE_H__
#define __RB_TREE_H__ 1

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef RB_ITER_MAX_HEIGHT
#define RB_ITER_MAX_HEIGHT 64 // Tallest allowable tree to iterate
#endif

typedef struct rb_node rb_node;
typedef struct rb_tree rb_tree;

typedef void *rb_key_ptr;
typedef void *rb_value_ptr;

typedef struct {
    rb_key_ptr   key;
    rb_value_ptr data;
} rb_data;

typedef int  (*rb_tree_node_cmp_f)(rb_key_ptr a, rb_key_ptr b);
typedef void (*rb_tree_node_free)(rb_node *node);

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

int rb_tree_node_cmp_ptr_cb(rb_key_ptr a, rb_key_ptr b);
void rb_tree_node_dealloc_cb(rb_node *node);

static inline
void *rb_malloc(size_t size) {
    return calloc(1, size);
}

static inline
rb_node *rb_node_alloc() {
    return rb_malloc(sizeof(rb_node));
}

static inline
rb_node *rb_node_init(rb_node *self, rb_data *value) {
    if (self) {
        self->red = 1;
        self->link[0] = self->link[1] = NULL;
        self->data = value;
    }
    return self;
}

static inline
rb_node *rb_node_create(rb_data *value) {
    return rb_node_init(rb_node_alloc(), value);
}

static inline
void rb_node_dealloc(rb_node *self) {
    if (self) {
        free(self);
    }
}

rb_node *rb_tree_insert_node(rb_tree *self, rb_node *node);
int rb_tree_remove_with_cb(rb_tree *self, rb_key_ptr key);

static inline
rb_tree *rb_tree_alloc() {
    return calloc(1, sizeof(rb_tree));
}

static inline
rb_tree *rb_tree_init(rb_tree *self, rb_tree_node_cmp_f node_cmp_cb, rb_tree_node_free node_free_cb) {
    if (self) {
        self->root = NULL;
        self->size     = 0;
        self->cmp_node = node_cmp_cb ? node_cmp_cb : rb_tree_node_cmp_ptr_cb;
        self->free_node= node_free_cb;
    }
    return self;
}

static inline
rb_tree *rb_tree_create(rb_tree_node_cmp_f node_cmp_cb, rb_tree_node_free node_free_cb) {
    return rb_tree_init(rb_tree_alloc(), node_cmp_cb, node_free_cb);
}

void rb_tree_dealloc(rb_tree *self);
rb_data *rb_tree_find(rb_tree *self, rb_key_ptr value);

static inline
rb_node *rb_tree_insert(rb_tree *self, rb_data *value) {
    return rb_tree_insert_node(self, rb_node_create(value));
}

static inline
int rb_tree_remove(rb_tree *self, rb_key_ptr value) {
    int result = 0;
    if (self) {
        result = rb_tree_remove_with_cb(self, value);
    }
    return result;
}

static inline
size_t rb_tree_size(rb_tree *self) {
    size_t result = 0;
    if (self) {
        result = self->size;
    }
    return result;
}


int rb_tree_test(rb_tree *self, rb_node *root);

static inline
rb_iter *rb_iter_init(rb_iter *self) {
    if (self) {
        self->tree = NULL;
        self->node = NULL;
        self->top  = 0;
    }
    return self;
}

rb_iter *rb_iter_create();

static inline
void rb_iter_dealloc(rb_iter *self) {
    if (self) {
        free(self);
    }
}

rb_data *rb_iter_move(rb_iter *self, int dir);
rb_data *rb_iter_start(rb_iter *self, rb_tree *tree, int dir);

static inline
rb_data *rb_iter_first(rb_iter *self, rb_tree *tree) {
    return rb_iter_start(self, tree, 0);
}

static inline
rb_data *rb_iter_last(rb_iter *self, rb_tree *tree) {
    return rb_iter_start(self, tree, 1);
}

static inline
rb_data *rb_iter_next(rb_iter *self) {
    return rb_iter_move(self, 1);
}

static inline
rb_data *rb_iter_prev(rb_iter *self) {
    return rb_iter_move(self, 0);
}

#endif
