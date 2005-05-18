/* $Id$ */

#include <stdio.h>
#include <stdarg.h>

#include "calclib.h"

struct cl_expr *
cl_expr_init(void)
{
	expr_t *expr;

	if ((expr = malloc(sizeof(*expr))) == NULL)
		return (NULL);
	expr->terms = NULL;
	expr->num_terms = 0;
	return (expr);
}

void
expr_free(expr_t *expr)
{
	term_t **t;

	if (expr == NULL)
		return;
	for (t = expr->terms; *t != NULL; t++)
		free(t);
	free(expr);
}

expr_t *
expr_parse(char *s, int len)
{
	expr_t *expr;
	int function_level = 0;
	int integral_level = 0;
	int derivative_level = 0;
	char *q;

	expr = Expression_init();

	for (q = s; (s != '\0') && (q-s < len); s++) {
		switch (*q) {
		case '(': {
			/* Parse sub-expression */
			char *t;
			int subexprs = 1;
			for (t = q; *t != '\0'; t++)
				switch (*t) {
				case '(':
					subexprs++;
					break;
				case ')':
					if (--subexprs < 0)
						/* Parse error */
						return;
					else if (subexprs == 0)
						break;
					break;
				}
			/* t now points to end of sub expression */
			subexpr = expr_parse(q, t-q);
			q = t+1;
			break;
		}
		case '-': case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7': case '8':
		case '9': case '.': {
			break;
		}
		case ' ':
			break;
		default:
		}
	}

	return (expr);
}
