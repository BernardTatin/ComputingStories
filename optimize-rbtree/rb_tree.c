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

#include "rb_tree.h"
#include "private_rb_tree.h"

// =====================================================================
// utility functions
rb_data *rb_get_data(rb_node *node) {
    return node->data;
}

rb_key_ptr rb_get_key(rb_node *node) {
    return node->data->key;
}

rb_value_ptr rb_get_value(rb_node *node) {
    return node->data->value;
}

rb_node *rb_node_create(rb_data *value) {
    return rb_node_init(rb_node_alloc(), value);
}


// =====================================================================
// rb_node

static inline int
rb_node_is_red (const rb_node *self) {
    return self ? self->red : 0;
}

static rb_node *
rb_node_rotate (rb_node *self, int dir) {
    rb_node *result = NULL;
    if (self) {
        result = self->link[!dir];
        self->link[!dir] = result->link[dir];
        result->link[dir] = self;
        self->red = 1;
        result->red = 0;
    }
    return result;
}

static rb_node *
rb_node_rotate2 (rb_node *self, int dir) {
    rb_node *result = NULL;
    if (self) {
        self->link[!dir] = rb_node_rotate(self->link[!dir], !dir);
        result = rb_node_rotate(self, dir);
    }
    return result;
}


// =====================================================================
// rb_tree

static inline rb_tree *rb_tree_alloc() {
    return calloc(1, sizeof(rb_tree));
}

static inline rb_tree *rb_tree_init(rb_tree *self, rb_tree_node_cmp_f node_cmp_cb, rb_tree_node_free node_free_cb) {
    if (self && node_cmp_cb && node_free_cb) {
        self->root      = NULL;
        self->size      = 0;
        self->cmp_node  = node_cmp_cb;
        self->free_node = node_free_cb;
        return self;
    }
    return self;
}

rb_tree *rb_tree_create(rb_tree_node_cmp_f node_cmp_cb, rb_tree_node_free node_free_cb) {
    return rb_tree_init(rb_tree_alloc(), node_cmp_cb, node_free_cb);
}

static rb_node *rb_tree_insert_node(rb_tree *self, rb_node *node);
rb_node *rb_tree_insert(rb_tree *self, rb_data *data) {
    return rb_tree_insert_node(self, rb_node_create(data));
}

size_t rb_tree_size(rb_tree *self) {
    size_t result = 0;
    if (self) {
        result = self->size;
    }
    return result;
}













void
rb_tree_dealloc (rb_tree *self) {
    if (self) {
        if (self->free_node) {
            rb_node *node = self->root;
            rb_node *save = NULL;

            // Rotate away the left links so that
            // we can treat this like the destruction
            // of a linked list
            while (node) {
                if (node->link[0] == NULL) {

                    // No left links, just kill the node and move on
                    save = node->link[1];
                    self->free_node(node);
                    rb_node_dealloc(node);
                    node = NULL;
                } else {

                    // Rotate away the left link and check again
                    save = node->link[0];
                    node->link[0] = save->link[1];
                    save->link[1] = node;
                }
                node = save;
            }
        }
        free(self);
    }
}

int
rb_tree_test (rb_tree *self, rb_node *root) {
    int lh, rh;

    if ( root == NULL )
        return 1;
    else {
        rb_node *ln = root->link[0];
        rb_node *rn = root->link[1];

        /* Consecutive red links */
        if (rb_node_is_red(root)) {
            if (rb_node_is_red(ln) || rb_node_is_red(rn)) {
                printf("Red violation");
                return 0;
            }
        }

        lh = rb_tree_test(self, ln);
        rh = rb_tree_test(self, rn);

        /* Invalid binary search tree */
        if ( ( ln != NULL && self->cmp_node(rb_get_key(ln), rb_get_key(root)) >= 0 )
            || ( rn != NULL && self->cmp_node(rb_get_key(rn), rb_get_key(root)) <= 0))
        {
            puts ( "Binary tree violation" );
            return 0;
        }

        /* Black height mismatch */
        if ( lh != 0 && rh != 0 && lh != rh ) {
            puts ( "Black violation" );
            return 0;
        }

        /* Only count black links */
        if ( lh != 0 && rh != 0 )
            return rb_node_is_red ( root ) ? lh : lh + 1;
        else
            return 0;
    }
}

rb_data *
rb_tree_find(rb_tree *self, rb_key_ptr key) {
    rb_data *result = NULL;
    if (self) {
        rb_node *it = self->root;
        while (it) {
            int cmp;
            if ((cmp = self->cmp_node(rb_get_key(it), key))) {

                // If the tree supports duplicates, they should be
                // chained to the right subtree for this to work
                it = it->link[cmp < 0];
            } else {
                break;
            }
        }
        result = it ? it->data : NULL;
    }
    return result;
}

// THIS COMMENT MUST BE REWRITTEN
// Returns NULL if not successful or node inserted but not found
// else return the existing node with the same data
static rb_node*
rb_tree_insert_node (rb_tree *self, rb_node *node) {
    rb_node *result = NULL;
    if (self && node) {
        if (self->root == NULL) {
            self->root = node;
            result = NULL;
        } else {
            rb_node head = { 0 }; // False tree root
            rb_node *g, *t;       // Grandparent & parent
            rb_node *p, *q;       // Iterator & parent
            int dir = 0, last = 0;

            // Set up our helpers
            t = &head;
            g = p = NULL;
            q = t->link[1] = self->root;

            // Search down the tree for a place to insert
            while (1) {
                if (q == NULL) {

                    // Insert node at the first null link.
                    p->link[dir] = q = node;
                } else if (rb_node_is_red(q->link[0]) && rb_node_is_red(q->link[1])) {

                    // Simple red violation: color flip
                    q->red = 1;
                    q->link[0]->red = 0;
                    q->link[1]->red = 0;
                }

                if (rb_node_is_red(q) && rb_node_is_red(p)) {

                    // Hard red violation: rotations necessary
                    int dir2 = t->link[1] == g;
                    if (q == p->link[last]) {
                        t->link[dir2] = rb_node_rotate(g, !last);
                    } else {
                        t->link[dir2] = rb_node_rotate2(g, !last);
                    }
                }

                // Stop working if we inserted a node. This
                // check also disallows duplicates in the tree
                if (q == node) {
                    // we are at the newly inserted node
                    result = NULL;
                    break;
                } else if (self->cmp_node(rb_get_key(q), rb_get_key(node)) == 0) {
                    // a node with the same data already exist
                    result = q;
                    break;
                }

                last = dir;
                dir = self->cmp_node(rb_get_key(q), rb_get_key(node)) < 0;

                // Move the helpers down
                if (g != NULL) {
                    t = g;
                }

                g = p, p = q;
                q = q->link[dir];
            }

            // Update the root (it may be different)
            self->root = head.link[1];
        }

        // Make the root black for simplified logic
        self->root->red = 0;
        ++self->size;
    }

    return result;
}

// Returns 1 if the data was removed, 0 otherwise. Optional node callback
// can be provided to dealloc node and/or user data. Use rb_tree_node_dealloc
// default callback to deallocate node created by rb_tree_insert(...).
int
rb_tree_remove_node (rb_tree *self, rb_key_ptr key) {
    if (self->root != NULL) {
        rb_node head = {0}; // False tree root
        //rb_node node = { .data = key }; // Value wrapper node
        rb_node *q, *p, *g; // Helpers
        rb_node *f = NULL;  // Found item
        int dir = 1;

        // Set up our helpers
        q = &head;
        g = p = NULL;
        q->link[1] = self->root;

        // Search and push a red node down
        // to fix red violations as we go
        while (q->link[dir] != NULL) {
            int last = dir;

            // Move the helpers down
            g = p, p = q;
            q = q->link[dir];
            dir = self->cmp_node(rb_get_key(q), key) < 0;

            // Save the node with matching data and keep
            // going; we'll do removal tasks at the end
            if (self->cmp_node(rb_get_key(q), key) == 0) {
                f = q;
            }

            // Push the red node down with rotations and color flips
            if (!rb_node_is_red(q) && !rb_node_is_red(q->link[dir])) {
                if (rb_node_is_red(q->link[!dir])) {
                    p = p->link[last] = rb_node_rotate(q, dir);
                } else if (!rb_node_is_red(q->link[!dir])) {
                    rb_node *s = p->link[!last];
                    if (s) {
                        if (!rb_node_is_red(s->link[!last]) && !rb_node_is_red(s->link[last])) {

                            // Color flip
                            p->red = 0;
                            s->red = 1;
                            q->red = 1;
                        } else {
                            int dir2 = g->link[1] == p;
                            if (rb_node_is_red(s->link[last])) {
                                g->link[dir2] = rb_node_rotate2(p, last);
                            } else if (rb_node_is_red(s->link[!last])) {
                                g->link[dir2] = rb_node_rotate(p, last);
                            }

                            // Ensure correct coloring
                            q->red = g->link[dir2]->red = 1;
                            g->link[dir2]->link[0]->red = 0;
                            g->link[dir2]->link[1]->red = 0;
                        }
                    }
                }
            }
        }

        // Replace and remove the saved node
        if (f) {
            void *tmp = f->data;
            f->data = q->data;
            q->data = tmp;

            p->link[p->link[1] == q] = q->link[q->link[0] == NULL];

            if (self->free_node) {
                self->free_node(q);
            }
            q = NULL;
        }

        // Update the root (it may be different)
        self->root = head.link[1];

        // Make the root black for simplified logic
        if (self->root != NULL) {
            self->root->red = 0;
        }

        --self->size;
    }
    return 1;
}

// rb_iter

static rb_iter *
rb_iter_alloc () {
    return rb_malloc(sizeof(rb_iter));
}

static inline
rb_iter *rb_iter_init(rb_iter *self) {
    if (self) {
        self->tree = NULL;
        self->node = NULL;
        self->top  = 0;
    }
    return self;
}

rb_iter *
rb_iter_create () {
    return rb_iter_init(rb_iter_alloc());
}

// Internal function, init traversal object, dir determines whether
// to begin traversal at the smallest or largest valued node.
rb_data *
rb_iter_start (rb_iter *self, rb_tree *tree, int dir) {
    void *result = NULL;
    if (self) {
        self->tree = tree;
        self->node = tree->root;
        self->top = 0;

        // Save the path for later selfersal
        if (self->node != NULL) {
            while (self->node->link[dir] != NULL) {
                self->path[self->top++] = self->node;
                self->node = self->node->link[dir];
            }
        }

        result = self->node == NULL ? NULL : self->node->data;
    }
    return result;
}

// Traverse a red black tree in the user-specified direction (0 asc, 1 desc)
rb_data *
rb_iter_move (rb_iter *self, int dir) {
    if (self->node->link[dir] != NULL) {

        // Continue down this branch
        self->path[self->top++] = self->node;
        self->node = self->node->link[dir];
        while ( self->node->link[!dir] != NULL ) {
            self->path[self->top++] = self->node;
            self->node = self->node->link[!dir];
        }
    } else {

        // Move to the next branch
        rb_node *last = NULL;
        do {
            if (self->top == 0) {
                self->node = NULL;
                break;
            }
            last = self->node;
            self->node = self->path[--self->top];
        } while (last == self->node->link[dir]);
    }
    return self->node == NULL ? NULL : self->node->data;
}

rb_data *rb_iter_first(rb_iter *self, rb_tree *tree) {
    return rb_iter_start(self, tree, 0);
}

rb_data *rb_iter_last(rb_iter *self, rb_tree *tree) {
    return rb_iter_start(self, tree, 1);
}

rb_data *rb_iter_next(rb_iter *self) {
    return rb_iter_move(self, 1);
}

rb_data *rb_iter_prev(rb_iter *self) {
    return rb_iter_move(self, 0);
}

void rb_iter_dealloc(rb_iter *self) {
    if (self) {
        free(self);
    }
}
