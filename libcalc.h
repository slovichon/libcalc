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

struct _variable
{
	char *name;
	int power;
};

struct _function
{
	Expression *operation;
	char *name;
};

struct _expression
{
	Term *terms;
	int num_terms;
};

struct _term
{
	double coefficient;
	Variable *variable;
	double exponent;
};

Term *Term_init(double, Variable *, double);
void Term_free(Term *);

Function *Function_init(char *, Expression *);
void Function_free(Function *);

Expression *Expression_init(void);
void Expression_free_(Expression *, char *, int);
#define Expression_free(p) Expression_free(p, __FILE__, __LINE__);
Expression *parse_string(char *s);

Variable *Variable_init(char *name);
void Variable_free(Variable *);

#endif /* _CALCLIB_H */
