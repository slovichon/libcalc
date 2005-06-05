/* $Id$ */

#include "libcalc.h"

struct cl_expr *
cl_deriv(struct cl_expr *expr, struct cl_var *var)
{
	struct cl_deriv_var cldv;
	struct cl_deriv cld;

	cldv.cldv_var = var;
	cldv.cldv_deg = 1;

	SLIST_INIT(&cld.cld_vars);
	SLIST_INSERT_HEAD(&cld.cld_vars, cldv, cldv_next);

	return (cl_deriv_v(expr, cld));
}

struct cl_deriv {
	SLIST_HEAD(cl_deriv_var)	 cld_vars;
};

struct cl_deriv_var {
	struct cl_var			*cldv_var;
	size_t				 cldv_deg;
	SLIST_ENTRY(cl_deriv_var)	 cldv_next;
}

struct cl_expr *
cl_deriv_v(struct cl_expr *expr, struct cl_deriv *cld)
{
	struct cl_deriv_var *cldv;
	struct cl_expr *deriv, *d;
	size_t deg;

	if ((deriv = cl_expr_copy(expr)) == NULL)
		return (NULL);
	SLIST_FOREACH(&cld.cld_vars, cldv, cldv_next) {
		for (deg = 0; deg < cldv->cldv_deg; deg++) {
			if ((d = _cl_do_deriv(deriv,
			    cldv->cldv_var)) == NULL) {
				free(deriv);
				return (NULL);
			}
			free(deriv);
			deriv = d;
		}
	}
	return (deriv);
}

static struct cl_expr *
cl_do_deriv(struct cl_expr *expr, struct cl_var *var)
{
	
}
