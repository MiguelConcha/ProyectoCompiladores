%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <string.h>

	#include "attributes.h"
	#include "symtab.h"
	#include "typetab.h"
	#include "backpatch.h"
	#include "intermediate_code.h"

	extern int yylex();
	extern int yylineno;
	extern FILE *yyin;
	void yyerror(char *);

	void yyerror2(char*, char*);
	void yyerror(char *);

	/* Variable para el conteo de direcciones */
	int dir=0;

	/* Variables para guardar el tipo y ancho actual */
	int current_type;
	int current_dim;
	int current_arr_type;

	/* Varaibles para contar las temporales, etiquetas e indices */
	int label;
	int temp;
	int indice;

	/* Variable para el unico atributo heredado de sentencia prima*/
	labels lfalses;


	/* Variable para la tabla de símbolos*/
	symtab tabla_de_simbolos;
	typetab tabla_de_tipos;

	/* Variable papra guardar el código intermedio que se va generando */
	ic codigo_intermedio;


	/* Funciones auxiliares al análisis semántico y generación de código intermedio */
	void init();
	void finish();

	exp suma(exp e1, exp e2);
	exp resta(exp e1, exp e2);
	exp multiplicacion(exp e1, exp e2);
	exp division(exp e1, exp e2);
	exp get_numero(numero);
	exp identificador(char *);
	exp asignacion(char *id, exp e);

	/* Funciones auxiliares para la comprobación de tipos */
	int max(int t1, int t2);
	char *ampliar(char *dir, int t1, int t2);
	char *reducir(char *dir, int t1, int t2);


	/* Funciones para generar temporales, etiquetas e indices */
	char *newTemp();
	char *newLabel();
	char *newIndex();


%}

%union {
    numero num;    
    cadena cad;    
    caracter car;    
    arreglo arr;    
    char id[32];
    exp expresion;
    type tipo;
    struct{
		labels falses;
		labels trues;
    }booleanos;
    labels siguientes;
    struct{
        labels siguientes;
        int ifelse;
    }siguientesp;
    int rel;
}


%token END
%token INTTYPE FLOATTYPE DOUBLETYPE CHARTYPE VOID
%token FUNC
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
%token<id> ID 
%token<num> INT 
%token<num> DOUBLE 
%token<num> FLOAT 
%token<cad> CADENA 
%token<car> CARACTER 
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

%type<tipo> tipo
%type<num> numero
%type<arr> arreglo

%%

prog:
	{ printf("kk\n"); init();} decls { print_type_table(&tabla_de_tipos); print_table(&tabla_de_simbolos); } funcs { /*finish();*/ }
;

decls:
	 tipo { current_type = $1.type; current_dim = $1.dim; current_arr_type = current_type;} lista SEMICOLON decls 
	 | %empty 
;

tipo: 
	INTTYPE { $$.type = 0; $$.dim = 4; }
    | FLOATTYPE { $$.type = 1; $$.dim = 4; }
	| DOUBLETYPE { $$.type = 2; $$.dim = 8; }
	| CHARTYPE { $$.type = 3; $$.dim = 1; }
	| VOID { $$.type = 4; $$.dim = 1; }
	| STRUCT LCURLYB decls RCURLYB { $$.type = 8; $$.dim = 0; }  /* Tipo = 5, dim = decls.dim */
;

lista:
	 lista COMMA ID arreglo {
	 	sym s;
		strcpy(s.id, $3);
		s.type = current_arr_type;
		s.dir = dir;
		dir+= current_dim;
		insert(&tabla_de_simbolos, s);
		current_arr_type = current_type;
	 } 
	 | ID arreglo {
	 	sym s;
		strcpy(s.id, $1);
		s.type = current_arr_type;
		s.dir = dir;
		dir+= current_dim;
		insert(&tabla_de_simbolos, s);
		current_arr_type = current_type;
	 }
;

numero:
	INT { $$.type = $1.type; strcpy($$.val, $1.val); }
	| DOUBLE { $$.type = $1.type; strcpy($$.val, $1.val); }
	| FLOAT { $$.type = $1.type; strcpy($$.val, $1.val); }
;

arreglo:
	   LBRACKET numero RBRACKET arreglo {
	       if ($2.type != 0) {
		       yyerror("Te pasaste de verga. Mete tu entero!");
			   exit(1);
		   }
	       $$.tam = $4.tam + 1;
		   memcpy($$.dims, $4.dims, 1000);
		   $$.dims[$$.tam-1] = atoi($2.val);

		   typerow* tr = create_typerow(5, $$.tam, current_arr_type, NULL);
		   insert_type_table(&tabla_de_tipos, tr);
		   current_arr_type = tabla_de_tipos.count-1;
	   } 
	   | %empty { $$.tam = 0; }
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

void init(){    
    create_table(&tabla_de_simbolos);
    create_type_table(&tabla_de_tipos);
    create_code(&codigo_intermedio);
    create_labels(&lfalses);    
	print_type_table(&tabla_de_tipos);
}

void finish(){    
    print_code(&codigo_intermedio);    
}

void yyerror(char *msg) {
	printf("%s\n", msg);
}

int main(int argc, char **argv) {
	FILE *r = fopen(argv[1], "r");
	yyin = r;
	int result = yyparse();
	printf("%d\n", result);
	fclose(r);
	return 0;
}
