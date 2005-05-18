/* $Id$ */

#include <stdlib.h>

#include "libcalc.h"

struct cl_expr *
cl_expr_init(void)
{
	struct cl_expr *expr;

	if ((expr = malloc(sizeof(*expr))) == NULL)
		return (NULL);
	SLIST_INIT(&expr->clx_terms);
	return (expr);
}

void
cl_expr_free(struct cl_expr *expr)
{
	struct cl_term *t, *tp;

	if (expr == NULL)
		return;
	for (t = SLIST_FIRST(&expr->clx_terms); t != NULL; t = tp) {
		tp = SLIST_NEXT(t, clt_next);
		cl_term_free(t);
	}
	free(expr);
}

struct cl_expr *
cl_expr_parse(const char *s, struct cl_parse *parse)
{
	int function_level = 0;
	int integral_level = 0;
	int derivative_level = 0;
	int subexprs = 1;
	struct cl_expr *expr, *subexpr;
	struct cl_parse subparse;
	const char *t, *q;

	expr = cl_expr_init();
	memset(&subparse, 0, sizeof(subparse));

	for (q = s; *q != '\0'; q++) {
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
			subparse.clp_options = CLPO_ALLOWNEST;
			subexpr = cl_expr_parse(q, &subparse);
			if (subexpr == NULL) {
				
			}
			if ()
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
