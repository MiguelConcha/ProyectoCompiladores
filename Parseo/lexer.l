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

int						{ increment(yytext); printf("%s\n", yytext); }
float					{ increment(yytext); printf("%s\n", yytext); }
double					{ increment(yytext); printf("%s\n", yytext); }
char					{ increment(yytext); printf("%s\n", yytext); }
func 					{ increment(yytext); printf("%s\n", yytext); }
void					{ increment(yytext); printf("%s\n", yytext); }
struct 					{ increment(yytext); printf("%s\n", yytext); }

"{"						{ increment(yytext); printf("%s\n", yytext); }
"}"						{ increment(yytext); printf("%s\n", yytext); }
"["						{ increment(yytext); printf("%s\n", yytext); }
"]"						{ increment(yytext); printf("%s\n", yytext); }
"("						{ increment(yytext); printf("%s\n", yytext); }
")"						{ increment(yytext); printf("%s\n", yytext); }
","						{ increment(yytext); printf("%s\n", yytext); }
";"						{ increment(yytext); printf("%s\n", yytext); }
"."						{ increment(yytext); printf("%s\n", yytext); }

true					{ increment(yytext); printf("%s\n", yytext); }
false					{ increment(yytext); printf("%s\n", yytext); }

if						{ increment(yytext); printf("%s\n", yytext); }
else					{ increment(yytext); printf("%s\n", yytext); }
while 					{ increment(yytext); printf("%s\n", yytext); }
for 					{ increment(yytext); printf("%s\n", yytext); }
do						{ increment(yytext); printf("%s\n", yytext); }
switch 					{ increment(yytext); printf("%s\n", yytext); }
case{TP}				{ increment(yytext); printf("%s\n", yytext); }
default{TP}				{ increment(yytext); printf("%s\n", yytext); }
break					{ increment(yytext); printf("%s\n", yytext); }
print					{ increment(yytext); printf("%s\n", yytext); }

"&&"					{ increment(yytext); printf("%s\n", yytext); }
"||"					{ increment(yytext); printf("%s\n", yytext); }
">="					{ increment(yytext); printf("%s\n", yytext); }
"<="					{ increment(yytext); printf("%s\n", yytext); }
"<"						{ increment(yytext); printf("%s\n", yytext); }
">"						{ increment(yytext); printf("%s\n", yytext); }
"!="					{ increment(yytext); printf("%s\n", yytext); }
"=="					{ increment(yytext); printf("%s\n", yytext); }
"!"						{ increment(yytext); printf("%s\n", yytext); }
"+"						{ increment(yytext); printf("%s\n", yytext); }
"-"						{ increment(yytext); printf("%s\n", yytext); }
"*"						{ increment(yytext); printf("%s\n", yytext); }
"/"						{ increment(yytext); printf("%s\n", yytext); }
"%"						{ increment(yytext); printf("%s\n", yytext); }
"="						{ increment(yytext); printf("%s\n", yytext); }

{caracter}				{ increment(yytext); printf("%s\n", yytext); }
{cadena}				{ increment(yytext); printf("%s\n", yytext); }
{ID}					{ increment(yytext); printf("%s\n", yytext); }
{int}					{ increment(yytext); printf("%s\n", yytext); 
						  }
{double}				{ increment(yytext); printf("%s\n", yytext); 
						  }
{float}					{ increment(yytext); printf("%s\n", yytext); 
						  }

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

/*
int main(int argc, char **argv) {
	yyin = fopen(argv[1], "r");
	yylex();
	fclose(yyin);
	return 0;
}*/
