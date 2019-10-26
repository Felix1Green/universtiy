%{
#include <stdio.h>
int desq_seq(char* yytext){
	int count = 0;
	for(int i = 0; i < yyleng-1; i++){
		if(yytext[i] < yytext[i+1] || (count ==0 && yytext[i] != yytext[i+1])){
			return 0;
		}else if(yytext[i] != yytext[i+1]){
			count = 0;
		}else{
			count++;
		}
		
	}return count;
}
%}
%%

([1-9][0-9]+)* {
		if(desq_seq(yytext))
			printf("Ответ: %s\n",yytext);
	}
.|\n+ ;
%%

int main(){
	yylex();
	return(0);
}
