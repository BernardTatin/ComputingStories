# `rb_tree`, un *red-black tree*

Le code original est de Mirek Rusin <http://github.com/mirek/rb_tree>. Les modifications que j'ai apportées correspondent à ce dont j'ai besoin, rien ne prouve qu'elles soient fondamentalement bonnes ni qu'elles soient exemptent d'erreur, *i.e.* j'ai pu introduire des bugs (plus ou moins subtils).

Pour résumer, j'adapte l'API à mes besoins immédiats. L'intérêt est immense, ça me permet de conserver l'agilité de mon esprit durant cette retraite que j'estime avoir mérité.

## les types de données

Les structures et les types importants sont:

```C
typedef struct rb_node rb_node;
typedef struct rb_tree rb_tree;

typedef void *rb_key_ptr;
typedef void *rb_value_ptr;

typedef int  (*rb_tree_node_cmp_f)(rb_key_ptr a, rb_key_ptr b);
typedef void (*rb_tree_node_free)(rb_node *node);
```

Voici le détail des structures:

```C
typedef struct {
    rb_key_ptr   key;
    rb_value_ptr data;
} rb_data;

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
```

À plus ou moins long terme, `rb_node` et `rb_tree` devraient être *opaques* - ce qui m'obligerait à supprimer le `inline` et ça m'embête pour l'instant.
