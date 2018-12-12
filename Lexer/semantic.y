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

	void finish();
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
	exp asignacion(char *, char *, exp, int);

    exp envolver_varr(varr);
    exp envolver_cadena(cadena);
    exp envolver_caracter(caracter);

	void meter_assign(cuadrupla [], int);
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
	argumentos argu;
    char id[32];
	pii pi;	
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
	char char_signo[1];
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
%left IFX
%left ELSE

%type<tipo> tipo
%type<num> numero
%type<arr> arreglo
%type<cant> decls
%type<cant> lista
%type<expresion> exp
%type<vararr> var_arr
%type<rel> rel
%type<booleanos> cond
%type<siguientes> sent sents assign
%type<siguientesp> sentp
%type<pi> parte_izq
%type<char_signo> signo
%type<argu> args lista_args

%start prog

%%

prog:
	{ init(); } decls 
	funcs	
    {
	 	print_type_table(masterchef->tt);
		print_table(masterchef->st); 
        printf("P -> D funcs\n"); /*finish()*/
		finish(); 
    }
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
		ntab->st= (symtab *) malloc(sizeof(symtab));
		create_table(ntab->st);
		create_type_table(ntab->tt);
		stack_masterchefs = mete(stack_masterchefs, ntab);
	  } 
	  decls RCURLYB { 
		struct mastertab* sacada;// = (struct mastertab *) malloc(sizeof(struct mastertab));
		sacada = tope(stack_masterchefs); 
		stack_masterchefs = saca(stack_masterchefs);

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
	signo INT { $$.type = $2.type; strcpy($$.val, $1); strcat($$.val, $2.val); }
	| signo DOUBLE { $$.type = $2.type; strcpy($$.val, $1); strcat($$.val, $2.val); }
	| signo FLOAT { $$.type = $2.type; strcpy($$.val, $1); strcat($$.val, $2.val); }
;

signo: 
	 PLUS { strcpy($$,""); }
	 | MINUS { strcpy($$, "-"); }
	 | %empty { strcpy($$,""); }
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
		   insert_type_table(stack_masterchefs->tabla->tt, renglon);
		   current_arr_type = stack_masterchefs->tabla->tt->count-1;
	   } 
	   | %empty { $$.tam = 0; }
;

funcs:
	 FUNC tipo ID LPAR args RPAR {
	 	sym s;
		strcpy(s.id, $3);
		s.type = $2.type;
		s.dir = stack_masterchefs->tabla->tt->count;
		s.var = 1;
		for(int j = 0; j < $5.num; j++){
			s.args[j] = $5.lista_args[j];
		}
		s.num_args = $5.num;
		insert(stack_masterchefs->tabla->st, s);

		struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
		ntab->tt = (typetab *) malloc(sizeof(typetab));
		ntab->st= (symtab *) malloc(sizeof(symtab));
		create_table(ntab->st);
		create_type_table(ntab->tt);
		stack_masterchefs = mete(stack_masterchefs, ntab);

	 }
	 LCURLYB decls sents {
        cuadrupla c;
        char label[32];
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$10));
        insert_cuad(&codigo_intermedio, c);                
        strcpy(label, newLabel());                                                
        backpatch(&$10, label, &codigo_intermedio);
	 }
	 RCURLYB {
		struct mastertab* sacada;// = (struct mastertab *) malloc(sizeof(struct mastertab));
		sacada = tope(stack_masterchefs); 
		stack_masterchefs = saca(stack_masterchefs);

		typerow renglon;
		renglon.type = 7;
		renglon.tam = $9.cantidad;
		renglon.base.renglon = -2;
		renglon.base.smt = sacada;
		insert_type_table(stack_masterchefs->tabla->tt, renglon);
	  	//$$.type = stack_masterchefs->tabla->tt->count-1; 
		//$$.bytes = $4.cantidad; 
	 } funcs 
	 | %empty 
;

args:
	lista_args { $$.num = $1.num; 
				 for(int i = 0; i < $1.num; i++){
					$$.lista_args[i] = $1.lista_args[i];
				 }
			   }
	| %empty { $$.num = 0; }
;

lista_args:
		  lista_args COMMA tipo ID parte_arr  {
		  		$$.num = 1 + $1.num;
				 for(int i = 0; i < $1.num; i++){
					$$.lista_args[i] = $1.lista_args[i];
				 }
				 //FALTA CHECAR BIEN EL TIPO PARA CASOS MULTIDIMENSIONALES
				 $$.lista_args[$$.num-1] = $3.type;
		  } 
		  | tipo ID parte_arr {
			     $$.num = 1;
				 $$.lista_args[0] = $1.type;
		  }
;

parte_arr:
		 LBRACKET RBRACKET parte_arr 
		 | %empty 
;

sents:
	sents {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$1));
        insert_cuad(&codigo_intermedio, c);                                
    }
    sent {
        char label[32];
        strcpy(label, newLabel());                                
        $$ = $3;                
        backpatch(&$1, label, &codigo_intermedio);                
        printf("SS->SS S\n");
    } 
    | sent {
        char label[32];
        strcpy(label, newLabel());
        $$ = $1;
        backpatch(&$1, label, &codigo_intermedio);
        printf("SS->S\n");
    }
;

sent:
	IF LPAR cond RPAR {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$3.trues));
        insert_cuad(&codigo_intermedio, c);
    }
    sent {
        cuadrupla c, c1;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$6));
        push_label(&lfalses, get_first(&$3.falses));
        insert_cuad(&codigo_intermedio, c);
    } sentp {
        char label[32];
        strcpy(label, newLabel());
        
        if($8.ifelse==false){
            $$ = merge(&$3.falses, &$8.siguientes);
            backpatch(&$3.falses, label, &codigo_intermedio);                                
            printf("S->if(B) S\n");
        }else{
            char label2[32];                                    
            strcpy(label2, newLabel());                
            $$ = merge(&$6,&$8.siguientes);
            backpatch(&$3.trues, label, &codigo_intermedio);
            backpatch(&$3.falses, label2, &codigo_intermedio);                 
            printf("S->if(B)S else S\n");
        }
    }
    | WHILE LPAR cond RPAR sent {
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                
        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
		printf("tempito %s /n", temp);
        $$ = $3.falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&$3.trues, label, &codigo_intermedio);
        backpatch(&$3.falses, label2, &codigo_intermedio);
        printf("S->while(B)S\n");
    }
    | DO sent WHILE LPAR cond RPAR SEMICOLON {
		char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                

		//Ejecucion incondicional de la sentencia
		backpatch(&$5.trues, label, &codigo_intermedio);

        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
		printf("tempito %s /n", temp);
        $$ = $5.falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&$5.trues, label, &codigo_intermedio);
        backpatch(&$5.falses, label2, &codigo_intermedio);
        printf("S->do S while(B)\n");
	}
    | FOR LPAR assign SEMICOLON cond SEMICOLON assign RPAR sent {
		meter_assign($3.arr_codigo, $3.count_codigo);
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                
        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        printf("tempito %s /n", temp);
        $$ = $5.falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&$5.trues, label, &codigo_intermedio);
        backpatch(&$5.falses, label2, &codigo_intermedio);
		meter_assign($7.arr_codigo, $7.count_codigo);
        printf("S->for(ass; cond; ass) sent\n");
    }
	| assign SEMICOLON { meter_assign($1.arr_codigo, $1.count_codigo); }
	| RETURN exp SEMICOLON
	| RETURN SEMICOLON 
	| LCURLYB sents RCURLYB {
        char label[32];
        $$ = $2;                
        strcpy(label, newLabel());                
        backpatch(&$2, label, &codigo_intermedio);                                
        printf("S->{SS}\n");
    }  
	| SWITCH LPAR exp RPAR LCURLYB casos RCURLYB 
	| BREAK SEMICOLON  
	| PRINT exp SEMICOLON {
        char i[32];
        strcpy(i, newIndex());
        $$ = create_list(i);
        printf("S->print(E);\n");
    }
;

assign: 
	  parte_izq ASSIG exp {
                char i[32];
                strcpy(i, newIndex());
                $$ = create_list(i);
                printf("%s, %s, %d\n", $1.id1, $1.id2,$1.type);
                exp e = asignacion($1.id1, $1.id2, $3, $1.type); 
                printf("S->parte_izq = E;\n");
				int iterador;
				$$.count_codigo = e.count_codigo;
				for(iterador = 0; iterador < e.count_codigo; iterador++) {
					$$.arr_codigo[iterador] = e.arr_codigo[iterador];
				}
	} 
;

sentp:
	{ printf("sin else\n"); $$.ifelse= false;} %prec IFX
	| ELSE 
        {        
            cuadrupla c1;
            c1.op = LABEL;
            strcpy(c1.op1, "");
            strcpy(c1.op2, "");
            strcpy(c1.res, pop_label(&lfalses));
            insert_cuad(&codigo_intermedio, c1);
        } 
    sent { 
        $$.ifelse= true;
        $$.siguientes = $3;
    }
;

casos:
	 CASE numero sent casos 
	 | DEFAULT sent 
	 | %empty 
;

parte_izq:
		 ID { strcpy($$.id1, $1); strcpy($$.id2,""); $$.type = -1;}
	     | var_arr  { strcpy($$.id1, $1.representacion); $$.type = $1.type;}
		 | ID DOT ID { strcpy($$.id1, $1); strcpy($$.id2, $3); $$.type = -1;}
;

var_arr:
	   ID LBRACKET exp RBRACKET { if($3.type != 0) { 
                                    yyerror("Debes indexar el arreglo con un entero.\n"); 
                                  }
								  strcpy($$.representacion, $1);
								  strcat($$.representacion, "[");
								  strcat($$.representacion, $3.dir);
								  strcat($$.representacion, "]");
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
								  strcat($$.representacion, "[");
								  strcat($$.representacion, $3.dir);
								  strcat($$.representacion, "]");
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
        //strcpy($$.dir, $2.dir);
        printf("B->(B)\n");
    }
    | exp rel exp {
        char i[32];
        char i2[32];
        char temp[32];
        strcpy(i, newIndex());
        strcpy(i2, newIndex());
        strcpy(temp, newTemp());
        //strcpy($$.dir, temp);
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
	if(e1.type != 0 || e2.type != 0) {
		yyerror("La operación módulo requiere operandos enteros.\n");
		exit(1);
	}
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

int get_tipo_tablas(char *id) {
	int tipo;
	int busqueda = search(stack_masterchefs->tabla->st, id);
	if (busqueda == -1) {
		busqueda = search(masterchef->st, id);
		if (busqueda == -1) {
			yyerror("El identificador para la variable no fue declarada antes.\n");
			exit(1);
		} else {	
			tipo = get_type(masterchef->st, id);
		}
	} else {
		tipo = get_type(stack_masterchefs->tabla->st, id);
	}
	return tipo;
}

exp asignacion(char *id, char *id2, exp e, int trecibido){
	exp e1;
	e1.count_codigo = 0;
	if(trecibido == -1) {
		int tipo;
		int es_estruct = 0;
		if(strcmp(id2, "") == 0) {
			tipo = get_tipo_tablas(id);
		} else {
			es_estruct = 1;
			int renglon = search(masterchef->st, id);
			if (renglon == -1) {
				yyerror("El identificador no fue declarado\n");
				exit(1);
			}
			typetab tabla_tipos_actual= (*masterchef->tt);
			int tiene_struct = tabla_tipos_actual.trs[masterchef->st->symbols[renglon].type].base.renglon;
			if(tiene_struct == -2) {
				symtab *st_struct = tabla_tipos_actual.trs[stack_masterchefs->tabla->st->symbols[renglon].type].base.smt->st;
				int renglon2 = search(st_struct, id2);
				if (renglon2 == -1) {
					st_struct = tabla_tipos_actual.trs[masterchef->st->symbols[renglon].type].base.smt->st;
					renglon2 = search(st_struct, id2);
					if(renglon2 == -1) {
						yyerror("El struct no fue declarado\n");
						exit(1);
					}
				}
				tipo = get_type(st_struct, id2);
			} else {
				yyerror2("Intento de acceso a atributo de no estructura: ", id);
				exit(1);
			}
		}

		if( tipo != -1){        
			printf("djekjde");
			e1.type = e.type;
			strcpy(e1.dir, id);
			cuadrupla c;
			c.op = ASSIGNATION;
			strcpy(c.op1, reducir(e.dir, tipo, e.type));
			strcpy(c.op2, "");
			if(es_estruct == 1) {
				char id_con_punto[65];
				strcpy(id_con_punto, id);
				strcat(id_con_punto, ".");
				strcat(id_con_punto, id2);
				strcpy(c.res, id_con_punto);
			} else {
				strcpy(c.res, id);
			}
			//insert_cuad(&codigo_intermedio, c);  
			e1.arr_codigo[e1.count_codigo] = c;	
			e1.count_codigo++;
		}else{
			yyerror("El identificador no fue declarado\n");
			exit(1);
		}
	} else {
		// VARARR
		e1.type = e.type;
		strcpy(e1.dir, id);
		cuadrupla c;
		c.op = ASSIGNATION;
		strcpy(c.op1, reducir(e.dir, trecibido, e.type));
		strcpy(c.op2, "");
		strcpy(c.res, id);//en este caso id es la representacin de vararr
		//insert_cuad(&codigo_intermedio, c);  
		e1.arr_codigo[e1.count_codigo] = c;
		e1.count_codigo++;}
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
    strcpy(e.dir, arreglito.representacion);
    return e;
}

exp identificador(char *id){
    exp e;
    if(search(stack_masterchefs->tabla->st, id) !=-1){
        e.type = get_type(stack_masterchefs->tabla->st, id);
        strcpy(e.dir, id);
    }else{
    	if(search(masterchef->st, id) !=-1){
         	e.type = get_type(masterchef->st, id);
        	strcpy(e.dir, id);
        } else {
        	yyerror("Error semantico: el identificador no existe");
    		exit(1);
    	}
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
	//faltan casos inconsistentes chars vs numeros vs arrays
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

void yyerror2(char *c, char *c2){
    strcat(c, c2);
	yyerror(c);
}

void finish(){    
    print_code(&codigo_intermedio);    
}

void meter_assign(cuadrupla c[], int cou){
	for(int j = 0; j < cou; j++){
		insert_cuad(&codigo_intermedio, c[j]);
		printf("metemos ass\n");
		printf("%s, %s, %s, %d", c[j].op1, c[j].op2, c[j].res, c[j].op);
	}
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
