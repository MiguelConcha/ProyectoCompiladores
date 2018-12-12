%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "attributes.h"
	#include "parser.tab.h"
	void lexical_error(int, int, char);
	void increment(char *);
	int col = 1;
%}

TP	:
n1  [0-9]+\.[0-9]*
n2	\.[0-9]+
ID [_a-zA-Z][_a-zA-Z0-9]{0,31}	
int	[0-9]+
decimal ({n1}|{n2})
double {decimal}|{int}	
float	{double}[Ff]
cadena \"[\x00-\x21\x23-\x7F]*\" 
caracter '[\x00-\x26\x28-\x7F]' 
 
%option noyywrap
%option yylineno

%x comentario

%%

"/*"					{ BEGIN(comentario); }
<comentario>[^"*/"]*	{ }
<comentario>"*/"		{ BEGIN(INITIAL); } 
<comentario><<EOF>>		{ printf("%s\n", "Error léxico: faltó cerrar el comentario."); exit(1); }

int						{ increment(yytext); printf("%s\n", yytext); return INTTYPE; }
float					{ increment(yytext); printf("%s\n", yytext); return FLOATTYPE; }
double					{ increment(yytext); printf("%s\n", yytext); return DOUBLETYPE; }
char					{ increment(yytext); printf("%s\n", yytext); return CHARTYPE; }
func 					{ increment(yytext); printf("%s\n", yytext); return FUNC; }
void					{ increment(yytext); printf("%s\n", yytext); return VOID; }
struct 					{ increment(yytext); printf("%s\n", yytext); return STRUCT; }

"{"						{ increment(yytext); printf("%s\n", yytext); return LCURLYB; }
"}"						{ increment(yytext); printf("%s\n", yytext); return RCURLYB; }
"["						{ increment(yytext); printf("%s\n", yytext); return LBRACKET; }
"]"						{ increment(yytext); printf("%s\n", yytext); return RBRACKET; }
"("						{ increment(yytext); printf("%s\n", yytext); return LPAR; }
")"						{ increment(yytext); printf("%s\n", yytext); return RPAR; }
","						{ increment(yytext); printf("%s\n", yytext); return COMMA; }
";"						{ increment(yytext); printf("%s\n", yytext); return SEMICOLON; }
"."						{ increment(yytext); printf("%s\n", yytext); return DOT; }

true					{ increment(yytext); printf("%s\n", yytext); return TRUE; }
false					{ increment(yytext); printf("%s\n", yytext); return FALSE; }

if						{ increment(yytext); printf("%s\n", yytext); return IF; }
else					{ printf("elsin\n"); increment(yytext); printf("%s\n", yytext); return ELSE; }
while 					{ increment(yytext); printf("%s\n", yytext); return WHILE; }
for 					{ increment(yytext); printf("%s\n", yytext); return FOR; }
do						{ increment(yytext); printf("%s\n", yytext); return DO; }
switch 					{ increment(yytext); printf("%s\n", yytext); return SWITCH; }
case{TP}				{ increment(yytext); printf("%s\n", yytext); return CASE; }
default{TP}				{ increment(yytext); printf("%s\n", yytext); return DEFAULT; }
break					{ increment(yytext); printf("%s\n", yytext); return BREAK; }
print					{ increment(yytext); printf("%s\n", yytext); return PRINT; }

"&&"					{ increment(yytext); printf("%s\n", yytext); return AND; }
"||"					{ increment(yytext); printf("%s\n", yytext); return OR; }
">="					{ increment(yytext); printf("%s\n", yytext); return GEQ; }
"<="					{ increment(yytext); printf("%s\n", yytext); return LEQ; }
"<"						{ increment(yytext); printf("%s\n", yytext); return LT; }
">"						{ increment(yytext); printf("%s\n", yytext); return GT; }
"!="					{ increment(yytext); printf("%s\n", yytext); return NEQ; }
"=="					{ increment(yytext); printf("%s\n", yytext); return EQ; }
"!"						{ increment(yytext); printf("%s\n", yytext); return NOT; }
"+"						{ increment(yytext); printf("%s\n", yytext); return PLUS; }
"-"						{ increment(yytext); printf("%s\n", yytext); return MINUS; }
"*"						{ increment(yytext); printf("%s\n", yytext); return PROD; }
"/"						{ increment(yytext); printf("%s\n", yytext); return DIV; }
"%"						{ increment(yytext); printf("%s\n", yytext); return MOD; }
"="						{ increment(yytext); printf("%s\n", yytext); return ASSIG; }

{caracter}				{ increment(yytext); printf("%s\n", yytext); return CARACTER; }
{cadena}				{ increment(yytext); printf("%s\n", yytext); return CADENA; }
{ID}					{ increment(yytext); printf("%s\n", yytext); return ID; }
{int}					{ increment(yytext); printf("%s\n", yytext); 
						  return INT; }
{double}				{ increment(yytext); printf("%s\n", yytext); 
						  return DOUBLE; }
{float}					{ increment(yytext); printf("%s\n", yytext); 
						  return FLOAT; }

[ \t\r\f\b]+			{ increment(yytext); }
\n						{ col = 1; }
.						{ increment(yytext); 
						  lexical_error(yylineno, col, yytext[0]);
						  exit(1); 
						}

%%

void increment(char *cadena) {
		int size = (int)strlen(cadena);
		col += size;
}

void lexical_error(int line, int column, char c) {
	FILE *e = fopen("lexical_errors.txt", "w");
	printf("Ocurrió un error léxico: \nLínea: %d\nColumna: %d\nCarácter que lo ocasiona: %c\n\n", line, column, c);
	fprintf(e,  "Ocurrió un error léxico: \nLínea: %d\nColumna: %d\nCarácter que lo ocasiona: %c\n\n", line, column, c);
	fclose(e);
}
