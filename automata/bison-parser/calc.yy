%{
#include <cmath>
#include <cstdio>
#include <cctype>

int yylex(void);
void yyerror(const char *);
%}

%define api.value.type union
%token <double> NUM
%type <double> exp
%left '-' '+'
%left '*' '/'
%precedence NEG
%right '^'

%%
input:
  %empty
| input line
;

line:
  '\n'
| exp '\n' { printf ("\t%g\n", $1); }
;

exp:
  NUM
| exp '+' exp { $$ = $1 + $3; }
| exp '-' exp { $$ = $1 - $3; }
| exp '*' exp { $$ = $1 * $3; }
| exp '/' exp { $$ = $1 / $3; }
| '-' exp %prec NEG { $$ = -$2; }
| exp '^' exp { $$ = pow ($1, $3); }
| '(' exp ')' { $$ = $2; }
;
%%

int yylex(void) {
  int c;
  while ((c = getchar()) == ' ' || c == '\t')
    continue;

  if (c == EOF)
    return 0;

  if (c == '.' || isdigit(c)) {
    ungetc(c, stdin);
    if (scanf("%lf", &yylval.NUM) != 1)
      abort();
    return NUM;
  }

  return c;
}

void yyerror(const char *s) {
  fprintf(stderr, "%s\n", s);
}

int main(int argc, const char *argv[]) {
  return yyparse();
}
