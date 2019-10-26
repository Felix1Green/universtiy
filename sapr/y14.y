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
    | error '\n' {yyerrok; }
    | exp0 exp1 '\n' {if(2*$1 != $2) yyerror("syntax error\n");}     
   

exp0: ZERO {$$++;}
    | exp0 ZERO {$$++;}
;
 
exp1: ONE{$$++;}
    | exp1 ONE {$$++;}
;
   
%%
int yylex(void)
{
    int c;
    c=getchar();
    if(c=='1')
    return ZERO;
    if(c=='0')
    return ONE;
    if (c==EOF)
        return 0;
       
    return c;
}
     
void yyerror(char const *s)
{
     fprintf(stderr, "%s\n", s);      
}
