%{
#include <math.h>
#include <stdio.h>
#include <string.h>
%}

id [a-zA-Z_][a-zA-Z0-9_]*
digit [0-9]
whitespace [ \t\n]+
binop [+\-*/]

%%
{digit}+ {
  printf("int: %s (%d)\n", yytext, atoi(yytext));
}

{digit}+"."{digit}+ {
  printf("float: %s (%g)\n", yytext, atof(yytext));
}

{id} {
  printf("identifier: %s\n", yytext);
}

{binop} {
  printf("binary op: %s\n", yytext);
}

"(" {
  printf("left paren: %s\n", yytext);
}

")" {
  printf("right paren: %s\n", yytext);
}

":=" {
  printf("assignment: %s\n", yytext);
}

{whitespace} // eat up whitespace

. {
  printf("unknown: %s\n", yytext);
}
%%

int main() {
  yyin = stdin;
  yylex();
  return 0;
}
