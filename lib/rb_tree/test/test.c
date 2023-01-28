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
typedef struct _iovec {
	void  *iov_base; // [XSI] Base address of I/O memory region
	size_t iov_len;  // [XSI] Size of region iov_base points to
} iovec;


// la fonction de comparaison nécessaire au tri et à la recherche
int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
    iovec *a = (iovec *) node_a->value;
    iovec *b = (iovec *) node_b->value;
    return (a->iov_len < b->iov_len) - (a->iov_len > b->iov_len);
}

unsigned long all_fuzzy[MAX_LOOPS];

unsigned long fuzzy_ul(const unsigned long kmin, const unsigned long kmax) {
	unsigned long k = (unsigned long)random() % kmax;
	unsigned long r = 0;
	static unsigned long unity = 1;
	while (all_fuzzy[(int)k] == 0) {
		if (unity == -1 && (k + unity) > kmax - 1) {
			k = kmax - 1;
		} else {
			k = (k + unity) % kmax;
		}
	}
	unity *= -1;
	r = all_fuzzy[(int)k];
	all_fuzzy[(int)k] = 0;
	return r;
}

void test(const int loops) {
	struct rb_tree *tree = rb_tree_create(my_cmp_cb);
	fprintf(stdout, "The tree: create\n");
	if (tree) {

		// Fill the tree here...
		for (unsigned long i = 1; i <= (unsigned long)loops; i++) {
			iovec *v = malloc(sizeof *v);
			unsigned long k = fuzzy_ul(MIN_LOOPS, (unsigned int)loops);
			v->iov_base = (void *) k;
			v->iov_len = k * k;

			printf("- %08p %6zu\n", v->iov_base, v->iov_len);
			// Default insert, which allocates internal rb_nodes for you.
			rb_tree_insert(tree, v);
		}

		// How to search
		unsigned long to_find = 70UL;
		iovec *f = rb_tree_find(tree, & (iovec) {
				.iov_base = (void *) to_find,
				.iov_len = 49
				});
		if (f) {
			fprintf(stdout, "found iovec(.iov_base = %08p, .iov_len = %6zu)\n",
					f->iov_base, f->iov_len);
		} else {
			printf("not found\n");
		}

		// How to iterate over the tree
		fprintf(stdout, "The tree: show\n");
		struct rb_iter *iter = rb_iter_create();
		if (iter) {
			for (iovec *v = rb_iter_last(iter, tree); v; v = rb_iter_prev(iter)) {
				printf("- %08p %6zu\n", v->iov_base, v->iov_len);
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
	for (int i=0; i<MAX_LOOPS; i++) {
		all_fuzzy[i] = (unsigned long)(i + 1);
	}
	test(loops);
	return 0;
}

