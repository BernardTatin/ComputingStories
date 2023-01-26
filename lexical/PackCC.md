# PackCC, un parser *packrat*

## coder le parser

Le parser doit créer un *contexte* en l'associant si besoin est à une *variable auxiliaire* déclarée dans `%auxil` et définie plus loin. Sans *variable auxiliaire*:

```yacc
%header {
	/* cool stuff */
}

%source {
	/* cool stuff */
}

# rules
# more cool stuff

%%
int main() {
	/* no auxil, we give NULL */
	calc_context_t *ctx = calc_create(NULL);
    while (calc_parse(ctx, NULL));
    calc_destroy(ctx);	
}
```

Avec *variable auxiliaire*:

```yacc
%auxil "SchemeAuxil *"

%header {
	typedef struct _SchemeAuxil {
		...
	} SchemeAuxil;
}

%source {
	/* cool stuff */
    /* Returns NULL on failure. Please check. */
    SchemeAuxil* create_auxiliary(...) {
      SchemeAuxil* aux = malloc(sizeof(SchemeAuxil));
      if (aux) {
        // initialize other needed auxiliary data fields
      }
      return aux;
    }

    void destroy_auxiliary(SchemeAuxil* aux) {
      if (aux) {
        // delete other auxiliary data fields
        free(aux);
      }
    }	
}

# rules
# more cool stuff

%%
int main() {
	/* no auxil, we give NULL */
	SchemeAuxiliary* aux = create_auxiliary(...);
	calc_context_t *ctx = calc_create(NULL);
    while (calc_parse(ctx, NULL));
    destroy_auxiliary(aux);
    calc_destroy(ctx);	
}
```



## lire depuis un fichier

Par défaut, *PackCC* lit les données en entrée un caractère à la fois depuis ` stdin` avec un simple appel à `getchar()`.   Pour lire depuis un fichier, il faut modifier la macro `PCC_GETCHAR(auxil)`.

Voici un bout de code permettant de lire un fichier (*cf.* [Stackoverflow](https://stackoverflow.com/questions/74910775/how-to-change-packcc-input-from-stdin-to-a-file)): 

```yacc
%auxil "SchemeAuxil*"
%value "ast*"

%header {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

// This could go in a different header. 
typedef struct SchemeAuxil {
  FILE* infile;
  // ... Any other needed auxiliary data
} SchemeAuxil;

} # %header

%source {
#define PCC_GETCHAR(auxil) fgetc(auxil->infile)

/*
 * This might go in a separate file, along with other support routines.
 * In that case, you would also create a header file to declare the support
 * functions, and put the #include for the header file in the %header block
 * above. 
 */

/* Returns NULL on failure. Please check. */
SchemeAuxil* create_auxiliary(FILE* infile) {
  SchemeAuxil* aux = malloc(sizeof *aux);
  if (aux) {
    aux->infile = infile;
    // initialize other needed auxiliary data fields
  }
  return aux;
}

void destroy_auxiliary(SchemeAuxil* aux) {
  if (aux) {
    if (aux->infile) fclose(aux->infile);
    // delete other auxiliary data fields
    free(aux);
  }
}

/* This replaces your parser_read function */
static void parser_read(const char *contents, int mode) {
    FILE *fp = fopen(contents, "r");
    
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    /* We should check that both create_auxiliary and scheme_create
     * returned non-NULL values.
     */
    SchemeAuxiliary* aux = create_auxiliary(fp);
    scheme_context_t *ctx = scheme_create(aux);
    ast *my_ast = NULL;

    // Should check the return value of scheme_parse.
    scheme_parse(ctx, &my_ast);
    ast_print(my_ast);
    eval_ast(my_ast);
    // delete ast
    destroy_auxiliary(aux);
    scheme_destroy(ctx);
}
} # %source

```

