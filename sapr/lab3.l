word  (1|0(11|00)*(10|01))(11|00|(10|01)(11|00)*(10|01))*
%{
	#include <stdio.h>
%}
%%
{word} printf("Ответ: %s\n", yytext);
({word}*[^{word}[:space:]]+{word}*)|[[:space:]]+ ;
