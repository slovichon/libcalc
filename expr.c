#include "calclib.h"
#include <stdio.h>
#include <stdarg.h>

static void bark(char *msg, ...)
{
	va_list ap;
	fprintf(stderr, "[ERR] ");
	va_start(ap, msg);
	vfprintf(stderr, msg, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	fflush(stderr);
}

Expression *Expression_init()
{
	Expression *p;
	p = xmalloc(sizeof(Expression));
	p->terms = NULL;
	p->num_terms = 0;
	return p;
}

void Expression_free_(Expression **p, char *file, int line)
{
	if (p && *p) {
		Term **t;
		for (t = p->terms; *t != NULL; t++)
			free(t);
		free(*p);
		*p = NULL;
	}
}

Expression *Expression_parse_str(char *s, int len)
{
	Expression *p;
	int function_level = 0;
	int integral_level = 0;
	int derivative_level = 0;
	char *q;

	p = Expression_init();

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
				subexpr = Expression_parse_str(q, t-q);
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

	return p;
}
