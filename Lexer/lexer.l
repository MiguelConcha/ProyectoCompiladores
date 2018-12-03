%{
	#include <iostream>
	#include "tokens.h"
	using namespace std;
	void error_lexico(string);
%}

TP	:
n1  [0-9]+\.[0-9]*
n2	\.[0-9]+
ID [_a-zA-Z][_a-zA-Z0-9]*	
int	[+-]?[0-9]+
decimal [+-]?({n1}|{n2})
double {decimal}|{int}	
float	{double}f 
cadena \"[\x00-\x21\x23-\x7F]*\" 
caracter '[\x00-\x26\x28-\x7F]' 
 
%option noyywrap
%option yylineno

%x comentario

%%

"/*"					{ BEGIN(comentario); }
<comentario>[^"*/"]*	{ }
<comentario>"*/"		{ BEGIN(INITIAL); } 
<comentario><<EOF>>		{ error_lexico("Error léxico: faltó cerrar el comentario."); }

int						{ cout << "inttype" << endl; return INTTYPE; }
float					{ cout << "floatype" << endl; return FLOATTYPE; }
double					{ cout << "doubletype" << endl; return DOUBLETYPE; }
char					{ cout << "chartype" << endl; return CHARTYPE; }
func 					{ cout << "func" << endl; return FUNC; }
void					{ cout << "void" << endl; return VOID; }
struct 					{ cout << "struct" << endl; return STRUCT; }

"{"						{ cout << "lcurly" << endl; return LCURLYB; }
"}"						{ cout << "rcurly" << endl; return RCURLYB; }
"["						{ cout << "lbracket" << endl; return LBRACKET; }
"]"						{ cout << "rbracket" << endl; return RBRACKET; }
"("						{ cout << "lpar" << endl; return LPAR; }
")"						{ cout << "rpar" << endl; return RPAR; }
";"						{ cout << "semicolon" << endl; return SEMICOLON; }
"."						{ cout << "point" << endl; return POINT; }

true					{ cout << "true" << endl; return TRUE; }
false					{ cout << "false" << endl; return FALSE; }

if						{ cout << "if" << endl; return IF; }
else					{ cout << "else" << endl; return ELSE; }
while 					{ cout << "while" << endl; return WHILE; }
do						{ cout << "do" << endl; return DO; }
switch 					{ cout << "switch" << endl; return SWITCH; }
case{TP}				{ cout << "case" << endl; return CASE; }
default{TP}				{ cout << "default" << endl; return DEFAULT; }
break					{ cout << "break" << endl; return BREAK; }
print					{ cout << "print" << endl; return PRINT; }

"&&"					{ cout << "AND" << endl; return AND; }
"||"					{ cout << "OR" << endl; return OR; }
"<"						{ cout << "LT" << endl; return LT; }
">"						{ cout << "GT" << endl; return GT; }
">="					{ cout << "GEQ" << endl; return GEQ; }
"<="					{ cout << "LEQ" << endl; return LEQ; }
"!="					{ cout << "NEQ" << endl; return NEQ; }
"=="					{ cout << "EQ" << endl; return EQ; }

{caracter}				{ cout << "CARACTER" << endl; return FLOAT; }
{cadena}				{ cout << "CADENA" << endl; return FLOAT; }
{ID}					{ cout << "ID" << endl; return ID; }
{int}					{ cout << "INT" << endl; return INT; }
{double}				{ cout << "DOUBLE" << endl; return DOUBLE; }
{float}					{ cout << "FLOAT" << endl; return FLOAT; }

[ \t\r\f]				{ }
<<EOF>>					{ return END; }
.						{ error_lexico("Ocurrió un error léxico."); }

%%

void error_lexico(string cadena) {
	cout << cadena << endl;
}

int main() {
	yylex();
	return 0;
}
