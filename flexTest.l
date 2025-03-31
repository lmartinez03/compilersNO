%{
/* a text program that adds line #s to lines of texts, printing the new text 
   to the standard output   
*/
#include <stdio.h>
int lineno = 1;
%}
line .*\n
%%
{line} {printf("%5d %s ", lineno++, yytext); }
%%
main()
{yylex; return 0;}