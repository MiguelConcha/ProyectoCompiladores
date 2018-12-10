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

	/* Variable para guardar el código intermedio que se va generando */
	ic codigo_intermedio;


	/* Funciones auxiliares al análisis semántico y generación de código intermedio */
	void init();

	exp suma(exp e1, exp e2);
	exp resta(exp e1, exp e2);
	exp multiplicacion(exp e1, exp e2);
	exp division(exp e1, exp e2);
	exp modulo(exp e1, exp e2);
	exp get_numero(numero);
	exp identificador(char *);
	exp asignacion(char *id, exp e);

    exp envolver_varr(varr);
    exp envolver_cadena(cadena);
    exp envolver_caracter(caracter);

 	int max(int t1, int t2);
  	char *ampliar(char *dir, int t1, int t2);
  	char *reducir(char *dir, int t1, int t2);

  	/* Funciones para generar temporales, etiquetas e indices */
	char *newTemp();
	char *newLabel();
	char *newIndex();

%}

%union {
	struct {
		int cantidad;
	} cant;
    varr vararr;
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
%type<expresion> exp
%type<vararr> var_arr
%type<rel> rel
%type<booleanos> cond

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
	 lista SEMICOLON decls {$$.cantidad = $3.cantidad; $$.cantidad += $5.cantidad; } /*no estamos seguros*/
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
	   ID LBRACKET exp RBRACKET { if($3.type != 0) { 
                                    yyerror("Debes indexar el arreglo con un entero.\n"); 
                                  }
                                  struct nodo* it = stack_masterchefs;
                                  int encontrado = 0;
                                  while(it != NULL) {
                                    int x = search(it->tabla->st, $1); 
                                    if(x != -1) {
                                        encontrado = 1;
                                        int type_row = it->tabla->st->symbols[x].type;
                                        $$.type = it->tabla->tt->trs[type_row].base.renglon;
                                        if($$.type == -1) {
                                            yyerror("No seas pendejo. Mayor cantidad de dimensiones que las definidas");
                                            exit(1);
                                        }
                                        break;
                                    }
                                    it = it->siguiente;
                                  }
                                  if(!encontrado) {
                                    yyerror("El arreglo no fue declarado antes.\n");
                                    exit(1);
                                  } 
                                  $$.tt = it->tabla->tt; }//valor   
       | var_arr LBRACKET exp RBRACKET { 
                                  if($3.type != 0) { 
                                    yyerror("Debes indexar el arreglo con un entero.\n"); 
                                  }
                                  if($1.type == -1) {
                                    yyerror("No seas pendejo. Mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  }  
                                  int row_hijo = $1.type;
                                  $$.type = (*$1.tt).trs[row_hijo].base.renglon;
                                  if($$.type == -1) {
                                    yyerror("No seas pendejo. Mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  }  
                                  $$.tt = $1.tt;

       }
;

exp:
   exp PLUS exp { $$ = suma($1, $3); printf("E -> E + E\n"); }  
   | exp MINUS exp { $$ = resta($1, $3); printf("E -> E - E\n"); }  
   | exp PROD exp { $$ = multiplicacion($1, $3); printf("E -> E * E\n"); } 
   | exp DIV exp { $$ = division($1, $3); printf("E -> E / E\n"); } 
   | exp MOD exp { $$ = modulo($1, $3); printf("E -> E mod E\n"); } 
   | var_arr { $$ = envolver_varr($1); printf("E -> id[E]\n"); }
   | ID { $$ = identificador($1); printf("E->id\n"); printf("%s\n",$1); } 
   | CADENA { $$ = envolver_cadena($1); printf("E -> CADENA\n"); }
   | numero { $$ = get_numero($1); printf("E->numero\n"); printf("%s\n",$1.val); }
   | CARACTER { $$ = envolver_caracter($1); printf("E -> CARACTER\n"); }
   | ID LPAR params RPAR {}
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
	cond OR {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$1.falses));
        insert_cuad(&codigo_intermedio, c);                    
    } cond { 
        char label[32];
        strcpy(label, newLabel());
        backpatch(&$1.falses, label, &codigo_intermedio);
        $$.trues = merge(&$1.trues, &$4.trues);
        $$.falses = $4.falses;
        printf("B -> B || B\n");
    }
    | cond AND {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$1.trues));
        insert_cuad(&codigo_intermedio, c);                    
    } cond {
        char label[32];
        strcpy(label, newLabel());                        
        $$.falses = merge(&$1.falses, &$4.falses);
        $$.trues = $4.trues;
        backpatch(&$1.trues, label, &codigo_intermedio);
        printf("B -> B && B\n");
    }
    | NOT cond {
        $$.falses = $2.trues;
        $$.trues = $2.falses;
        printf("B -> !B\n");
    }
    | LPAR cond RPAR {
        $$.trues = $2.trues;
        $$.falses = $2.falses;
        printf("B->(B)\n");
    }
    | exp rel exp {
        char i[32];
        char i2[32];
        char temp[32];
        strcpy(i, newIndex());
        strcpy(i2, newIndex());
        strcpy(temp, newTemp());
        $$.trues = create_list(i);
        $$.falses = create_list(i2);
        cuadrupla c, c1, c2;
        c.op = $2 ;
        strcpy(c.op1, $1.dir);
        strcpy(c.op2, $3.dir);
        strcpy(c.res, temp);            
        
        c1.op = IFF;
        strcpy(c1.op1, temp);
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, i);            
        
        c2.op = GOTO;
        strcpy(c2.op1, "");
        strcpy(c2.op2, "");
        strcpy(c2.res, i2);
        
        insert_cuad(&codigo_intermedio, c);
        insert_cuad(&codigo_intermedio, c1);
        insert_cuad(&codigo_intermedio, c2);
        printf("B->E rel E\n");
        printf("E1.dir %s rel E2.dir %s\n", $1.dir, $3.dir);
    }
    | TRUE {
        char i[32];
        strcpy(i, newIndex());
        $$.trues = create_list(i);
        cuadrupla c;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        insert_cuad(&codigo_intermedio, c);
        printf("B->true\n");
    } 
    | FALSE {
        char i[32];
        strcpy(i, newIndex());
        $$.falses = create_list(i);
        cuadrupla c;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        insert_cuad(&codigo_intermedio, c);
        printf("B->false\n");
    } 
;

rel:
   LT { $$ = LESS_THAN; printf("R-> <\n"); }
   | GT { $$ = GREATER_THAN; printf("R-> >\n"); }
   | LEQ { $$ = LESS_OR_EQUAL_THAN; printf("R-> <=\n"); }
   | GEQ { $$ = GREATER_OR_EQUAL_THAN; printf("R-> >=\n"); }
   | NEQ { $$ = NOT_EQUALS; printf("R-> !=\n"); }
   | EQ { $$ = EQUALS; printf("R-> ==\n"); } 
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

    create_code(&codigo_intermedio);
    create_labels(&lfalses);    
}

int max(int t1, int t2){
	if( t1==t2) return t1;
	if( t1 ==0 && t2 == 1) return 1;
	if( t1 ==1 && t2 == 0) return 1;
	if( t1 ==0 && t2 == 2) return 2;
	if( t1 ==2 && t2 == 0) return 2;
	if( t1 ==2 && t2 == 1) return 2;
	if( t1 ==1 && t2 == 2) return 2;
	else return -1;
}

exp suma(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MAS;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp resta(exp e1, exp e2){
    exp e;
    cuadrupla c;
    char t[32];
    e.type = max(e1.type, e2.type);
    
    if( e.type==-1) yyerror("Error de tipos");
    else{
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MENOS;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp multiplicacion(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MULTIPLICACION;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp division(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = DIVISION;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp modulo(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MODULO;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp asignacion(char *id, exp e){
    exp e1;
    int tipo = get_type(masterchef->st, id);
    if( tipo != -1){        
        e1.type = e.type;
        strcpy(e1.dir, id);
        cuadrupla c;
        c.op = ASSIGNATION;
        strcpy(c.op1, reducir(e.dir, tipo, e.type));
        strcpy(c.op2, "");
        strcpy(c.res, id);
        insert_cuad(&codigo_intermedio, c);  
        
    }else{
        yyerror("El identificador no fue declarado\n");
    }
    return e1;
}

exp get_numero(numero n){
    exp e;
    e.type = n.type;
    strcpy(e.dir, n.val);
    return e;
}

exp envolver_cadena(cadena cadenita) {
    exp e;
    e.type = cadenita.type;
    strcpy(e.dir, cadenita.val);
    return e;
}

exp envolver_caracter(caracter caractercito) {
    exp e;
    e.type = caractercito.type;
    e.dir[0] = caractercito.val;
    return e;
}

exp envolver_varr(varr arreglito) {
    exp e;
    e.type = arreglito.type;
    strcpy(e.dir, arreglito.dir);
    return e;
}

exp identificador(char *id){
    exp e;
    if(search(masterchef->st, id)!=-1){
        e.type = get_type(masterchef->st, id);
        strcpy(e.dir, id);
    }else{
        yyerror("Error semantico: el identificador no existe");
    }
    return e;
}

char *ampliar(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    
    if( t1==t2) return dir;
    if( t1 ==0 && t2 == 1){
        c.op = EQ;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        return t;
    }        
    if( t1 ==0 && t2 == 2){
        c.op = EQ;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        return t;
    }        
    
    if( t1 ==1 && t2 == 2) {
        c.op = EQ;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        return t;
    }            
}

char *reducir(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    
    if( t1==t2) return dir;
    if( t1 ==0 && t2 == 1){
        c.op = EQ;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un float a un int\n");
        return t;
    }        
    if( t1 ==0 && t2 == 2){
        c.op = EQ;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un int\n");
        return t;
    }        
    
    if( t1 ==1 && t2 == 2) {
        c.op = EQ;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un float\n");
        return t;
    }            
}

char* newTemp(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "t");
    char num[30];
    sprintf(num, "%d", temp);
    strcat(temporal, num);
    temp++;
    return temporal;
}

char* newLabel(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "L");
    char num[30];
    sprintf(num, "%d", label);
    strcat(temporal, num);
    label++;
    return temporal;
}

char* newIndex(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "I");
    char num[30];
    sprintf(num, "%d", indice);
    strcat(temporal, num);
    indice++;
    return temporal;
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
