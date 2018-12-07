%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <string.h>

	#include "attributes.h"
	#include "mastertab.h"
	#include "backpatch.h"
	#include "intermediate_code.h"
	#include "pila.h"

	extern int yylex();
	extern int yylineno;
	extern FILE *yyin;
	void yyerror(char *);
	void yyerror2(char*, char*);

	/* Variable para el conteo de direcciones */
	int dir=0;

	/* Variables para guardar el tipo y ancho actual */
	int current_type;
	int current_dim;
	int current_arr_type;
	int current_dim_arr;

	/* Varaibles para contar las temporales, etiquetas e indices */
	int label;
	int temp;
	int indice;

	/* Variable para el unico atributo heredado de sentencia prima*/
	labels lfalses;

	/*pila para las tablas*/
	struct nodo *stack_masterchefs; 

	/* Variable para la tabla de símbolos*/
	struct mastertab *masterchef;

	/* Variable papra guardar el código intermedio que se va generando */
	ic codigo_intermedio;


	/* Funciones auxiliares al análisis semántico y generación de código intermedio */
	void init();
%}

%union {
	struct {
		int cantidad;
	} cant;
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
    } booleanos;
    labels siguientes;
    struct{
        labels siguientes;
        int ifelse;
    } siguientesp;
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

%type<tipo> tipo
%type<num> numero
%type<arr> arreglo
%type<cant> decls
%type<cant> lista

%start prog

%%

prog:
	{ init(); } decls 
	{ print_type_table(masterchef->tt); print_table(masterchef->st); } 
	funcs { /*finish();*/ }
;

decls:
	 tipo { 
	 	current_type = $1.type;
		current_dim = $1.bytes;
		current_dim_arr = current_dim; 
		current_arr_type = current_type;
     } 
	 lista SEMICOLON decls {$$.cantidad = $3.cantidad; $$.cantidad += $5.cantidad ; printf("tam decls %d\n", $$.cantidad); } /*no estamos seguros*/
	 | %empty { $$.cantidad = 0; }
;

tipo: 
	INTTYPE { $$.type = 0; $$.bytes = 4; }
    | FLOATTYPE { $$.type = 1; $$.bytes = 4; }
	| DOUBLETYPE { $$.type = 2; $$.bytes = 8; }
	| CHARTYPE { $$.type = 3; $$.bytes = 1; }
	| VOID { $$.type = 4; $$.bytes = 1; }
	| STRUCT LCURLYB {
		struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
		ntab->tt = (typetab *) malloc(sizeof(typetab));
		ntab->st = (symtab *) malloc(sizeof(symtab));
		create_table(ntab->st);
		create_type_table(ntab->tt);
		stack_masterchefs = mete(stack_masterchefs, ntab);
	  } 
	  decls RCURLYB { 
	  	struct mastertab* sacada = (struct mastertab *) malloc(sizeof(struct mastertab));
		stack_masterchefs = saca(stack_masterchefs, sacada); 
		typerow renglon;
		renglon.type = 6;
		renglon.tam = $4.cantidad;
		renglon.base.renglon = -2;
		renglon.base.smt = sacada;
		insert_type_table(stack_masterchefs->tabla->tt, renglon);

	  	$$.type = stack_masterchefs->tabla->tt->count-1; $$.bytes = $4.cantidad; 
	  }  /* Tipo = 5, bytes = decls.bytes */
;

lista:
	 lista COMMA ID arreglo {
	 	sym s;
		strcpy(s.id, $3);
		s.type = current_arr_type;
		s.dir = dir;
		dir+= current_dim_arr;
		insert(stack_masterchefs->tabla->st, s);
		$$.cantidad  = current_dim_arr;
		current_arr_type = current_type;
		current_dim_arr = current_dim;
	 } 
	 | ID arreglo {
	 	sym s;
		strcpy(s.id, $1);
		s.type = current_arr_type;
		s.dir = dir;
		dir+= current_dim_arr;
		//insert(&tabla_de_simbolos, s);
		insert(stack_masterchefs->tabla->st, s);
		$$.cantidad  = current_dim_arr;
		current_arr_type = current_type;
		current_dim_arr = current_dim;
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
		   current_dim_arr *= atoi($2.val);
		   memcpy($$.dims, $4.dims, 1000);
		   $$.dims[$$.tam-1] = atoi($2.val);
		   typerow renglon;
		   renglon.type = 5;
		   renglon.tam = atoi($2.val);
		   renglon.base.renglon = current_arr_type;
		   renglon.base.smt = NULL;
		   //insert_type_table(&tabla_de_tipos, renglon);
		   insert_type_table(stack_masterchefs->tabla->tt, renglon);
		   current_arr_type = stack_masterchefs->tabla->tt->count-1;
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
	masterchef = (struct mastertab *) malloc(sizeof(struct mastertab));
	masterchef->tt = (typetab *) malloc(sizeof(typetab));
	masterchef->st = (symtab *) malloc(sizeof(symtab));
	stack_masterchefs = (struct nodo*) malloc(sizeof(struct nodo));
	stack_masterchefs = NULL;
    create_table(masterchef->st);
    create_type_table(masterchef->tt);

	stack_masterchefs = mete(stack_masterchefs, masterchef);

    //create_code(&codigo_intermedio);
    //create_labels(&lfalses);    
}

void yyerror(char *msg) {
	printf("%s\n", msg);
}

int main(int argc, char **argv) {
	yyin = fopen(argv[1], "r");
	//int a = yylex();
	//	printf("<<<<<%d\n", a);
	int result = yyparse();
	printf("resultado del analisis: %d\n", result);
	fclose(yyin);
	return 0;
}
