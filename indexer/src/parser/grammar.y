%{
/*
 * grammar.y
 *
 * Pascal grammar in Yacc format, based originally on BNF given
 * in "Standard Pascal -- User Reference Manual", by Doug Cooper.
 * This in turn is the BNF given by the ANSI and ISO Pascal standards,
 * and so, is PUBLIC DOMAIN. The grammar is for ISO Level 0 Pascal.
 * The grammar has been massaged somewhat to make it LALR, and added
 * the following extensions.
 *
 * constant expressions
 * otherwise statement in a case
 * productions to correctly match else's with if's
 * beginnings of a separate compilation facility
 */

%}

%token OPAREN CPAREN LCURLY RCURLY LSQUARE RSQUARE
%token DOT COMMA MINUS PIPE FSLASH STAR PLUS CARRET QUESTION
%token CHAR DELIM DIGIT ESCAPE
%token WHITESPACE CAP LOW ALPHA_NUM NUM

%%
file : regex;

regex : sequence PIPE regex
{
	Or *o = new Or();
	o->add($1);
	o->add($2);
	$$ = o;
};
regex : sequence { $$ = $1; } ;

sequence : quantifier sequence
{
	Sequence *seq = new Sequence();
	seq->add($1);
	seq->add($2);
	$$ = seq;
}
sequence : quantifier { $$ = $1; };

quantifier : base { $$ = $1; };
quantifier : base STAR
{
	Repitition *rep = new Repition();
	rep->add($1);
	$$ = rep;
};
quantifier : base PLUS;
{
	Sequence *seq = new Sequence();
	seq->add($1);
	
	Repitition *rep = new Repition();
	rep->add($1);
	seq->add(rep);
	
	$$ = seq;
};
quantifier : base QUESTION
{
	$$ = new Optional($1);
};
quantifier : base LCURLY number RCURLY
{
	Sequnce *seq = new Sequnce();
		
	$$ = seq;
};
quantifier : base LCURLY number COMMA RCURLY;
quantifier : base LCURLY number COMMA number RCURLY;

base : CHAR;
base : ESCAPE;
base : OPAREN regex CPAREN;
base : LSQUARE list RSQUARE;

number : DIGIT;
number : DIGIT number;

/* for now: */
list : CARROT list2;
list : list2;

list2 : CHAR list2;
list2 : CHAR;






