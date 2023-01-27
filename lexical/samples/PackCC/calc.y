%prefix "calc"
%auxil "CalcConfig *"

%header {
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "calc-tools.h"

typedef struct _CalcConfig {
	bool is_quiet;
	char *prompt_user;
	char *prompt_calc;
} CalcConfig;

}

%source {

CalcConfig *create_auxiliary(const bool is_quiet) {
	CalcConfig *conf = (CalcConfig *)malloc(sizeof(CalcConfig));
	if (conf != NULL) {
		conf->is_quiet = is_quiet;
		if (is_quiet) {
			conf->prompt_user = PROMPT_EMPTY;
			conf->prompt_calc = PROMPT_EMPTY;
		} else {
			conf->prompt_user = PROMPT_USER;
			conf->prompt_calc = PROMPT_CALC;
		}
	}
	return conf;
}

void destroy_auxiliary(CalcConfig *conf) {
	if (conf != NULL) {
		free(conf);
	}
}

void parse(const bool is_quiet) {
	CalcConfig *conf = create_auxiliary(is_quiet);
    calc_context_t *ctx = calc_create(conf);
    while (calc_parse(ctx, NULL))
		;
	destroy_auxiliary(conf);
    calc_destroy(ctx);
}

}

# rules
statement <- _ e:expression _ EOL { show_result(e, $0, auxil->is_quiet); }
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
		 / 'square' _ '(' _ e:expression _ ')' {
		 	$$ = (e) * (e);
		 } # BT
		 / 'gcd' _ '(' _ a:expression _ ',' _ b:expression _ ')' {
		 	$$ = gcd(a, b);
		 }
         / '(' _ e:expression _ ')' { $$ = e; }

_      <- [ \t]*
EOL    <- '\n' / '\r\n' / '\r' / ';'

%%
int main(int argc, char **argv) {
	bool quiet = false;
	if (argc == 2) {
		if (strcmp(argv[1], "-q") == 0) {
			quiet = true;
		}
	}
	if (!quiet) {
		printf("\nsuper calc, version %s (%s)\n\n", calc_version, __DATE__);
		printf("%s ", PROMPT_USER);
	}

	parse(quiet);

	if (!quiet) {
		printf("\n");
	}

    return 0;
}
