%prefix "calc"

%source {
#include <stdio.h>
#include <stdlib.h>

#include "calc-tools.h"
}

# rules
statement <- _ e:expression _ EOL { show_result(e, $0); }
           / ( !EOL . )* EOL      { printf("error\n%s ", PROMPT_USER); }

expression <- e:term { $$ = e; }

term <- l:term _ '+' _ r:factor { $$ = l + r; }
      / l:term _ '-' _ r:factor { $$ = l - r; }
      / e:factor                { $$ = e; }

factor <- l:factor _ '*' _ r:unary { $$ = l * r; }
        / l:factor _ '/' _ r:unary { $$ = l / r; }
        / l:factor _ '%' _ r:unary { $$ = l % r; } # BT
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
	printf("\nsuper calc, version %s (%s)\n\n", calc_version, __DATE__);
	printf("%s ", PROMPT_USER);

    calc_context_t *ctx = calc_create(NULL);
    while (calc_parse(ctx, NULL));
    calc_destroy(ctx);

	printf("\n");
    return 0;
}
