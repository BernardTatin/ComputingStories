//
// Based on Julienne Walker's <http://eternallyconfuzzled.com/> rb_tree
// implementation.
//
// Modified by Mirek Rusin <http://github.com/mirek/rb_tree>.
//
// Modified by Bernard Tatin
// (not sure it's very good but it fits well with my needs)
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

typedef struct rb_tree rb_tree;     // RB tree data type
typedef struct rb_node rb_node;     // node data type
typedef struct rb_iter rb_iter;     // iterator over a tree data type

typedef void *rb_key_ptr;           // key data type
typedef void *rb_value_ptr;         // value data type

// 3-way comparator function type
typedef int  (*rb_tree_node_cmp_f)(rb_key_ptr a, rb_key_ptr b);
// deallocation function data type
typedef void (*rb_tree_node_free)(rb_node *node);

// data structure, a pair of pointer on (key, value)
typedef struct {
    rb_key_ptr   key;
    rb_value_ptr value;
} rb_data;

// =====================================================================
// utility functions

// standard allocator, using calloc to be sure the data initialized to 0
static inline
void *rb_malloc(size_t size) {
    return calloc(1, size);
}

rb_data *rb_get_data(rb_node *);        // get the full data from a node
rb_key_ptr rb_get_key(rb_node *);       // get the key from a node
rb_value_ptr rb_get_value(rb_node *);   // get the value from a node

// =====================================================================
// Node API

rb_node *rb_node_create(rb_data *data);     // create a node and fill it with some data
int rb_tree_remove_node(rb_tree *self,      // remove the node with the specified key
                        rb_key_ptr key);

// =====================================================================
// RB tree API
// create a tree withe comparaison and allocation function pointer
rb_tree *rb_tree_create(rb_tree_node_cmp_f node_cmp_cb,
                        rb_tree_node_free node_free_cb);
// deallocate a tree
void rb_tree_dealloc(rb_tree *self);
// search a node with the specified key, return a pointer on the data struct
// or NULL if not found
rb_data *rb_tree_find(rb_tree *self,
                      rb_key_ptr key);
// insert a new data in a tree
rb_node *rb_tree_insert(rb_tree *self, rb_data *data);
// get the size of the tree
size_t rb_tree_size(rb_tree *self);


// =====================================================================
// Iterator API

rb_iter *rb_iter_create();              // create a new iterator
void rb_iter_dealloc(rb_iter *self);    // free an iterator

rb_data *rb_iter_first(rb_iter *self,   // get the first elt of the iteration
                       rb_tree *tree);
rb_data *rb_iter_last(rb_iter *self,    // get the last elt of the iteration
                      rb_tree *tree);
rb_data *rb_iter_next(rb_iter *self);   // get the next elt of the iteration
rb_data *rb_iter_prev(rb_iter *self);   // get the previous elt of the iteration

#endif
