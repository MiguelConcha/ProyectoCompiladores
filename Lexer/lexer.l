%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "attributes.h"
	#include "semantic.tab.h"
	void lexical_error(int, int, char);
	void increment(char *);
	int col = 1;
%}

TP	:
n1  [0-9]+\.[0-9]*
n2	\.[0-9]+
ID [_a-zA-Z][_a-zA-Z0-9]{0,31}	
int	[+-]?[0-9]+
decimal [+-]?({n1}|{n2})
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

int						{ printf("Leyendo int del lexer.\n"); increment(yytext); return INTTYPE; }
float					{ increment(yytext); return FLOATTYPE; }
double					{ increment(yytext); return DOUBLETYPE; }
char					{ increment(yytext); return CHARTYPE; }
func 					{ increment(yytext); return FUNC; }
void					{ increment(yytext); return VOID; }
struct 					{ increment(yytext); return STRUCT; }

"{"						{ increment(yytext); return LCURLYB; }
"}"						{ increment(yytext); return RCURLYB; }
"["						{ increment(yytext); return LBRACKET; }
"]"						{ increment(yytext); return RBRACKET; }
"("						{ increment(yytext); return LPAR; }
")"						{ increment(yytext); return RPAR; }
","						{ increment(yytext); return COMMA; }
";"						{ increment(yytext); return SEMICOLON; }
"."						{ increment(yytext); return DOT; }

true					{ increment(yytext); return TRUE; }
false					{ increment(yytext); return FALSE; }

if						{ increment(yytext); return IF; }
else					{ increment(yytext); return ELSE; }
while 					{ increment(yytext); return WHILE; }
for 					{ increment(yytext); return FOR; }
do						{ increment(yytext); return DO; }
switch 					{ increment(yytext); return SWITCH; }
case{TP}				{ increment(yytext); return CASE; }
default{TP}				{ increment(yytext); return DEFAULT; }
break					{ increment(yytext); return BREAK; }
print					{ increment(yytext); return PRINT; }
return					{ increment(yytext); return RETURN; }

"&&"					{ increment(yytext); return AND; }
"||"					{ increment(yytext); return OR; }
">="					{ increment(yytext); return GEQ; }
"<="					{ increment(yytext); return LEQ; }
"<"						{ increment(yytext); return LT; }
">"						{ increment(yytext); return GT; }
"!="					{ increment(yytext); return NEQ; }
"=="					{ increment(yytext); return EQ; }
"!"						{ increment(yytext); return NOT; }
"+"						{ increment(yytext); return PLUS; }
"-"						{ increment(yytext); return MINUS; }
"*"						{ increment(yytext); return PROD; }
"/"						{ increment(yytext); return DIV; }
"%"						{ increment(yytext); return MOD; }
"="						{ increment(yytext); return ASSIG; }

{caracter}				{ increment(yytext); /*yylval.car.type = 3; yylval.car.val = yytext[0];*/ return CARACTER; }
{cadena}				{ increment(yytext); /*strcpy(yylval.cad.val, yytext);*/ return CADENA; }
{ID}					{ increment(yytext); /*strcpy(yylval.id, yytext);*/ return ID; }
{int}					{ increment(yytext); 
						 /* yylval.num.type = 0; 
						  strcpy(yylval.num.val, yytext);*/ 
						  return INT; }
{double}				{ increment(yytext); 
					      /*yylval.num.type = 2;
						  strcpy(yylval.num.val, yytext);*/ 
						  return DOUBLE; }
{float}					{ increment(yytext); 
						 /* yylval.num.type = 1;
						  strcpy(yylval.num.val, yytext);*/ 
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
