%{
#include <stdio.h>
int yylex(void);
void yyerror(char const *);
%}

%token ZERO
%token ONE

%%
input: {printf("Enter the line:\n");}
     | input line;

line: '\n' {printf("Empty line\n");}
    | error '\n'  {yyerrok;}
    | exp2 '\n' {printf("correct!\n");}
    | exp2 exp1 '\n' {printf("correct!\n");}
    | exp1 '\n' {printf("correct!\n");}
	
exp1: ZERO ONE 
    | exp1 ZERO ONE 
    | exp1 ONE ;
    
exp2: ONE 
    | exp2 ONE ;
    
%%
int yylex(void)
{
    int c;
    c=getchar();
    if(c=='1')
    return ONE;
    if(c=='0')
    return ZERO;
    if (c==EOF)
        return 0;
        
    return c;
}
     
void yyerror(char const *s)
{
     fprintf(stderr, "%s\n", s);      
}
