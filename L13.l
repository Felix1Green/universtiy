%{
#include <stdio.h>
int AllNumbersAreDifferent(char* yytext){
	for (int i = 0; i < yyleng; i++){
		for (int j = i + 1; j < yyleng; j++){
			if (yytext[i] == yytext[j])
				return 0;
		}
	}
	return 1;
}
%}

%option noyywrap
%%

([1-9][0-9]+)* { 
		if (AllNumbersAreDifferent(yytext))
			printf("%s\n", yytext);
	}
([0-9]*[^0-9 '\040' '\012']+[0-9]*)* ;
.|\n+ ;
%%

int main(){
	yylex();
	return (0);
}

