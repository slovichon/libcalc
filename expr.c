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

void Expression_free_(Expression *p, char *file, int line)
{
	if (p) {
		Term *t;
		for (t = p->terms; t; t++)
			free(t);
		free(p);
	} else
		bark("Attempt to free uninitialized expression at %s:%d", file, line);
}

Expression *Expression_parse_str(char *s)
{
	Expression *p;
	int function_level = 0;
	int integral_level = 0;
	int derivative_level = 0;

	p = Expression_init();

	for (; s; s++) {
		
	}

	return p;
}
