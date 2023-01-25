%prefix "calc"

%source {
#include <stdio.h>
#include <stdlib.h>
}

statement <- _ e:expression _ EOL { printf(">= %6d\n>: ", e); }
           / ( !EOL . )* EOL      { printf("error\n>: "); }

expression <- e:term { $$ = e; }

term <- l:term _ '+' _ r:factor { $$ = l + r; }
      / l:term _ '-' _ r:factor { $$ = l - r; }
      / e:factor                { $$ = e; }

factor <- l:factor _ '*' _ r:unary { $$ = l * r; }
        / l:factor _ '/' _ r:unary { $$ = l / r; }
        / l:factor _ '%' _ r:unary { $$ = l % r; }
        / e:unary                  { $$ = e; }

unary <- '+' _ e:unary { $$ = +e; }
       / '-' _ e:unary { $$ = -e; }
       / e:primary     { $$ = e; }

primary <- < [0-9]+ >               { $$ = atoi($1); }
         / '(' _ e:expression _ ')' { $$ = e; }

_      <- [ \t]*
EOL    <- '\n' / '\r\n' / '\r' / ';'

%%
int main() {
    calc_context_t *ctx = calc_create(NULL);
	printf("super calc, version 0.0.1 (%s)\n", __DATE__);
	printf("Note: sizeof(int) = %lu\n", sizeof(int));
	printf(">: ");
    while (calc_parse(ctx, NULL));
    calc_destroy(ctx);
	printf("\n");
    return 0;
}
