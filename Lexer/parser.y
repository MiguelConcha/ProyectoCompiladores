%{
	#include <stdio.h>
    #include <stdlib.h>
	void yyerror(char *);
    extern int yylex();
    extern int yylineno;
%}

%token END
%token INTTYPE
%token FLOATTYPE
%token DOUBLETYPE
%token CHARTYPE
%token FUNC
%token VOID
%token STRUCT
%token LCURLYB
%token RCURLYB
%token LBRACKET 
%token RBRACKET 
%token SEMICOLON 
%token DOT
%token TRUE 
%token FALSE 
%token IF 
%token ELSE 
%token WHILE 
%token DO 
%token SWITCH 
%token CASE 
%token DEFAULT 
%token BREAK 
%token PRINT 
%token ID 
%token INT 
%token DOUBLE 
%token FLOAT 
%token CADENA 
%token CARACTER 
%token COMMA 
%token RETURN 
%token FOR 

%right ASSIG
%left OR
%left AND
%left EQ NEQ
%left GT GEQ
%left LT LEQ
%left PLUS MINUS
%left PROD DIV MOD
%right NOT
%left LBRACKET RBRACKET
%left LPAR RPAR  
%nonassoc "then"
%nonassoc ELSE

%start prog

%%

prog:
	decls funcs 
;

decls:
	 tipo lista SEMICOLON decls 
	 | %empty 
;

tipo: 
	INTTYPE 
    | FLOATTYPE 
	| DOUBLETYPE 
	| CHARTYPE 
	| VOID 
	| STRUCT LCURLYB decls RCURLYB 
;

lista:
	 lista COMMA ID arreglo  
	 | ID arreglo 
;

numero:
	  INT 
	  | DOUBLE 
	  | FLOAT 
;

arreglo:
	   LBRACKET numero RBRACKET arreglo  
	   | %empty 
;

funcs:
	 FUNC tipo ID LPAR args RPAR LCURLYB decls sents RCURLYB funcs  
	 | %empty 
;

args:
	lista_args  
	| %empty 
;

lista_args:
		  lista_args COMMA tipo ID parte_arr  
		  | tipo ID parte_arr 
;

parte_arr:
		 LBRACKET RBRACKET parte_arr 
		 | %empty 
;

sents:
	 sents sent 
     | sent 
;

sent:
	IF LPAR cond RPAR sent 				 %prec "then"
    | IF LPAR cond RPAR sent ELSE sent 
    | WHILE LPAR cond RPAR sent 
    | DO sent WHILE LPAR cond RPAR SEMICOLON 
    | FOR LPAR sent SEMICOLON cond SEMICOLON sent RPAR sent  
	| parte_izq ASSIG exp SEMICOLON 
	| RETURN exp SEMICOLON 
	| RETURN SEMICOLON 
	| LCURLYB sent RCURLYB  
	| SWITCH LPAR exp RPAR LCURLYB casos RCURLYB 
	| BREAK SEMICOLON  
	| PRINT exp SEMICOLON 
;

casos:
	 CASE numero sent casos 
	 | DEFAULT sent 
	 | %empty 
;

parte_izq:
		 ID 
	     | var_arr  
		 | ID DOT ID 
;

var_arr:
	   ID LBRACKET exp RBRACKET  
       | var_arr LBRACKET exp RBRACKET 
;

exp:
   exp PLUS exp  
   | exp MINUS exp 
   | exp PROD exp 
   | exp DIV exp 
   | exp MOD exp 
   | var_arr 
   | CADENA 
   | numero 
   | CARACTER 
   | ID LPAR params RPAR 
;

params:
	  lista_param 
	  | %empty 
;

lista_param:
		   lista_param COMMA exp  
   		   | exp 
;

cond:
	cond OR cond 
    | cond AND cond 
    | NOT cond 
    | LPAR cond RPAR 
    | exp rel exp 
    | TRUE 
    | FALSE 
;

rel:
   LT 
   | GT 
   | LEQ  
   | GEQ 
   | NEQ 
   | EQ 
;

%%

void yyerror (char *s) {
   fprintf (stderr, "%s\n", s);
}

int main() {
	return 0;
}
