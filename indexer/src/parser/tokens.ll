%{
 
#include <stdio.h>
#include "grammar.tab.h"
 
%}

/*{NUMBER}        { sscanf(yytext, "%d", &yylval->value); return TOKEN_NUMBER; }*/
 
%option outfile="Lexer.c" header-file="Lexer.h"
%option warn nodefault
 
%option reentrant noyywrap never-interactive
%option bison-bridge

OPAREN		"("
CPAREN		")"
LCURLY		"{"
RCURLY		"}"
LSQUARE		"["
RSQUARE		"]"
DOT			"."
COMMA		","
MINUS		"-"
PIPE		"|"
FSLASH		"/"
STAR		"*"
PLUS		"+"
CARRET		"^"
QUESTION	"?"
CHAR		[a-zA-Z0-9 \r\n\t]
DELIM		""
DIGIT		[0-9]
ESCAPE		"\"
 
%%

{OPAREN}	  {return OPAREN;}	
{CPAREN}	  {return CPAREN;}	
{LCURLY}	  {return LCURLY;}	
{RCURLY}	  {return RCURLY;}	
{LSQUARE}	  {return LSQUARE;}	
{RSQUARE}	  {return RSQUARE;}	
{DOT}		  {return DOT;}		
{COMMA}		  {return COMMA;}		
{MINUS}		  {return MINUS;}		
{PIPE}		  {return PIPE;}		
{FSLASH}	  {return FSLASH;}	
{STAR}		  {return STAR;}		
{PLUS}		  {return PLUS;}		
{CARRET}	  {return CARRET;}	
{QUESTION}	  {return QUESTION;}	
.             {  }
 
%%
 
int yyerror(const char *msg) {
    fprintf(stderr,"Error:%s\n",msg); return 0;
}
