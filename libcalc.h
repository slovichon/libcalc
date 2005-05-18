/* $Id$ */

#include <sys/queue.h>

enum clt_t {
	CLT_NUMBER,
	CLT_EXPR,
};

enum cl_op {
	CLOP_ADD,
	CLOP_SUB,
	CLOP_MULT,
	CLOP_DIV,
};

struct cl_var {
	char			*clv_name;
	union {
		struct cl_expr	*clvx_expr;
		double		 clvx_no;		/* Number */
	}			 clv_exp;		/* Exponent */
	enum clt_t		 clv_type;
#define clv_expr	clv_exponent.clvx_expr
#define clv_no		clv_exponent.clvx_no
};

struct cl_func {
	struct expr_t		*clf_expr;
	char			*clf_name;
};

struct cl_expr {
	SLIST_HEAD(, cl_term)	 clx_terms;
};

struct cl_term {
	double			 clt_coeff;		/* Coefficient */
	union {
		struct expr	*cltp_expr;
		struct var	*cltp_var;
	}			*clt_parts;
	struct expr		*clt_exps;		/* Exponents on parts */
	enum cl_op		*clt_ops;		/* Binding operations */
	SLIST_ENTRY(cl_term)	 clt_next;
#define clt_expr	clt_parts.cltp_expr
#define clt_var		clt_parts.cltp_var
};

struct cl_intg {
};

struct cl_lim {
};

struct cl_num {
};

struct cl_parser {
	int			 clp_options;
	int			 clp_error;
	const char		*clp_lastcp;
}

#define CLPO_ALLOWNEST (1<<0)

#define CLE_

struct cl_term			*cl_term_init(double, struct cl_var *, double);
void				 cl_term_free(struct cl_term *);

struct cl_func			*cl_func_init(const char *, struct cl_expr *);
void				 cl_func_free(struct cl_func *);

struct cl_expr			*cl_expr_init(void);
void				 cl_expr_free(struct cl_expr *);
struct cl_expr			*cl_expr_parse(const char *s, int);

struct cl_var			*cl_var_init(const char *name);
void				 cl_var_free(struct cl_var *);
