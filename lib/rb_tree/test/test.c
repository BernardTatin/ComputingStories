/*
 * test.c
 * testing rb-tree
 * cf. https://github.com/mirek/rb_tree
 */

#include <stdio.h>
#include <stdlib.h>

#include "../rb_tree.h"

#define DEFAULT_LOOPS 12
#define MIN_LOOPS 5
#define MAX_LOOPS 120

// la structure à stocker
struct iovec {
	void  *iov_base; // [XSI] Base address of I/O memory region
	size_t iov_len;  // [XSI] Size of region iov_base points to
};

// la fonction de comparaison nécessaire au tri
int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
    struct iovec *a = (struct iovec *) node_a->value;
    struct iovec *b = (struct iovec *) node_b->value;
    return (a->iov_len > b->iov_len) - (a->iov_len < b->iov_len);
}

void test(const int loops) {
	struct rb_tree *tree = rb_tree_create(my_cmp_cb);
	fprintf(stdout, "The tree: create\n");
	if (tree) {

		// Use the tree here...
		for (unsigned long i = 1; i <= (unsigned long)loops; i++) {
			struct iovec *v = malloc(sizeof *v);
			v->iov_base = (void *) i;
			v->iov_len = i * i;

			printf("- %p %zu\n", v->iov_base, v->iov_len);
			// Default insert, which allocates internal rb_nodes for you.
			rb_tree_insert(tree, v);
		}

		// To f
		unsigned long to_find = 70UL;
		struct iovec *f = rb_tree_find(tree, & (struct iovec) {
				.iov_base = (void *) to_find,
				.iov_len = 49
				});
		if (f) {
			fprintf(stdout, "found iovec(.iov_base = %p, .iov_len = %zu)\n", f->iov_base, f->iov_len);
		} else {
			printf("not found\n");
		}

		fprintf(stdout, "The tree: show\n");
		struct rb_iter *iter = rb_iter_create();
		if (iter) {
			for (struct iovec *v = rb_iter_last(iter, tree); v; v = rb_iter_prev(iter)) {
				printf("- %p %zu\n", v->iov_base, v->iov_len);
			}
			rb_iter_dealloc(iter);
		}

		// Dealloc call can take optional parameter to notify on each node
		// being deleted so you can free the node and/or your object:
		rb_tree_dealloc(tree, NULL);
	}
}

int main(int argc, char **argv) {
	int loops = DEFAULT_LOOPS;

	if (argc > 1) {
		int l = atoi(argv[1]);
		if (l < MIN_LOOPS) {
			l = MIN_LOOPS;
		} else if (l > MAX_LOOPS) {
			l = MAX_LOOPS;
		}
		loops = l;
	}
	test(loops);
	return 0;
}

