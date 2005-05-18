/* $Id$ */

#include <stdlib.h>

#include "libcalc.h"

struct cl_expr *
cl_expr_init(void)
{
	struct cl_expr_t *expr;

	if ((expr = malloc(sizeof(*expr))) == NULL)
		return (NULL);
	expr->terms = NULL;
	expr->num_terms = 0;
	return (expr);
}

void
cl_expr_free(struct cl_expr *expr)
{
	struct cl_term **t;

	if (expr == NULL)
		return;
	for (t = expr->terms; *t != NULL; t++)
		free(t);
	free(expr);
}

struct cl_expr *
cl_expr_parse(const char *s)
{
	struct cl_expr *expr;
	int function_level = 0;
	int integral_level = 0;
	int derivative_level = 0;
	int subexprs = 1;
	char *t, *q;

	expr = cl_expr_init();

	for (q = s; (s != '\0') && (q-s < len); s++) {
		switch (*q) {
		case '(':
			/* Parse sub-expression */
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
			subexpr = cl_expr_parse(q, t-q);
			q = t+1;
			break;
		case '-': case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7': case '8':
		case '9': case '.':
			break;
		case ' ': case '\t': case '\n':
			break;
		default:
			break;
		}
	}

	return (expr);
}
