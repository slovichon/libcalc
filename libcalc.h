/* $Id$ */
#ifndef _CALCLIB_H
#define _CALCLIB_H

struct _expression;
struct _term;
struct _function;
struct _variable;
typedef struct _expression Expression;
typedef struct _term Term;
typedef struct _function Function;
typedef struct _variable Variable;

enum clt_t {
	CLT_NUMBER,
	CLT_EXPR,
};

enum Operation {
	OP_ADD,
	OP_SUB,
	OP_MULT,
	OP_DIV,
};

struct _variable {
	char *name;
	union {
		Expression *expression;
		double number;
	} exponent;
	clt_t type;
};

struct _function {
	Expression *expression;
	char *name;
	/* char name; */
};

struct _expression {
	Term *terms;
};

struct _term {
	double coefficient;
	union {
		Expression *expression;
		Variable *variable;
	} *parts;
	/* Exponents on all the above parts */
	Expression *exponents;
	/* Binding operations between above parts */
	Operation *operations;
};

Term *Term_init(double, Variable *, double);
void Term_free(Term *);

Function *Function_init(char *, Expression *);
void Function_free(Function *);

Expression *Expression_init(void);
void Expression_free_(Expression *);
Expression *parse_string(char *s);

Variable *Variable_init(char *name);
void Variable_free(Variable *);

#endif /* _CALCLIB_H */
