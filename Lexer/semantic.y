/* 
 * Archivo: semantic.y
 * Authors: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedo Eduardo Eder
 * 			
 * Creado el 12 de diciembre de 2018.
 */

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <string.h>

    /* Atributos utilizados en los tokens y en los no terminales */
	#include "attributes.h"
	/* Tablas de tipos y símbolos */
	#include "mastertab.h"
	/* Backpatch */
	#include "backpatch.h"
	/* Código intermedio */
	#include "intermediate_code.h"
	/* Para las pilas de mastertabs */
	#include "pila.h"

    /* Variables que heredamos del analizador léxico. */
	extern int yylex();
	extern int yylineno;
	extern FILE *yyin;

    /* Funciones para escribir errores */
	void yyerror(char *);
	void yyerror2(char*, char*);

    /* Última función que se ejecutara. */
	void finish();

	/* Variable para el conteo de direcciones */
	int dir=0;

	/* Variables para guardar el tipo y ancho actual */
	int current_type;
	int current_dim;
	int current_arr_type;
	int current_dim_arr;
	int current_function_type;

	/* Variables para contar las temporales, etiquetas e indices */
	int label;
	int temp;
	int indice;
	int breakeablecitos = 0;

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

	/* Para funciones */
	void verifica_call(char[], int[], int);

%}

/* Declaración de los atributos que utilizaremos para los no terminales y los tokens */
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
	struct {
		int p;
		int lista_tipos[100];
		int count;
	} parrams;
}

/* Declaramos todos los tokens que utilizaremos */
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

/* Definimos la precedencia y la asociación de los operadores.
   Nos basamos en el manual del lenguaje de programación C. */
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

/* Definimos los atributos que utilizarán los no terminales. */
%type<tipo> tipo
%type<num> numero
%type<arr> arreglo
%type<cant> decls
%type<cant> lista
%type<expresion> exp
%type<parrams> lista_param
%type<parrams> params
%type<vararr> var_arr
%type<rel> rel
%type<booleanos> cond
%type<siguientes> sent sents assign
%type<siguientesp> sentp
%type<pi> parte_izq
%type<char_signo> signo
%type<argu> args lista_args

/* Definimos donde empezará el análisis. */
%start prog

%%

/* Regla de producción inicial.
   prog -> decls funcs */
prog:
	{ init(); } decls 
	funcs	
    {
        /* Imprimimos las tablas de tipo y símbolos y finalizamos. */
	 	print_type_table(masterchef->tt);
		print_table(masterchef->st); 
        printf("P -> D funcs\n");
		finish(); 
    }
;

/* Regla donde están todas las declaraciones de variables.
   decls -> tipo lista; decls | ɛ
   En las decls vamos actualizando el tipo actual para heredarlo a lista ya que ahí
   se agrega a la tabla de símbolos. */
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

/* Regla que nos donde se dice el tipo de las variables en lista.
   tipo -> int | float | double | char | void | struct { decls }
   En los tipo básicos sólo tenemos que asignarle el tipo del token al no terminal de tipo.
   Para los structs necesitamos agregarlos a la tabla de tipos. */
tipo: 
	INTTYPE { $$.type = 0; $$.bytes = 4; }
    | FLOATTYPE { $$.type = 1; $$.bytes = 4; }
	| DOUBLETYPE { $$.type = 2; $$.bytes = 8; }
	| CHARTYPE { $$.type = 3; $$.bytes = 1; }
	| VOID { $$.type = 4; $$.bytes = 1; }
	| STRUCT LCURLYB {
        /* Creamos una nueva mastertab donde guardaremos las declaraciones dentro del struct. Además
        agregamos este nuevo mastertab del struct al tope de la pila de mastertabs. */
        struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
        ntab->tt = (typetab *) malloc(sizeof(typetab));
        ntab->st= (symtab *) malloc(sizeof(symtab));
        create_table(ntab->st);
        create_type_table(ntab->tt);
        stack_masterchefs = mete(stack_masterchefs, ntab);
    } 
    decls RCURLYB { 
        /* Una vez que ya se hicieron todas las declaraciones del struct, entonces agregamos a la tabla
            de tipos el nuevo tipo del struct donde también le asociamos el mastertab que creamos para el
            struct. También quitamos de la pila de mastertabs el mastertab del struct. No se perderá ya
            que tendremos una referencia en la tabla de tipos a este mastertab. */
        struct mastertab* sacada;
        sacada = tope(stack_masterchefs); 
        stack_masterchefs = saca(stack_masterchefs);

        typerow renglon;
        renglon.type = 6;
        renglon.tam = $4.cantidad;
        renglon.base.renglon = -2;
        renglon.base.smt = sacada;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);

        $$.type = stack_masterchefs->tabla->tt->count-1; $$.bytes = $4.cantidad; 
    }
;

/* Regla donde se definen las variables con su tipo heredado.
   lista -> lista, id arreglo | id arreglo
   Aquí es donde se agrega a las tablas de simbolos los ids de las variables. */
lista:
	 lista COMMA ID arreglo {
	    /* Agregamos a la tabla de simbolos que esté en el tope de mastertabs. */
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
	    /* Agregamos a la tabla de simbolos que esté en el tope de mastertabs. */
	 	sym s;
		strcpy(s.id, $1);
		s.type = current_arr_type;
		s.dir = dir;
		dir+= current_dim_arr;
		insert(stack_masterchefs->tabla->st, s);
		$$.cantidad  = current_dim_arr;
		current_arr_type = current_type;
		current_dim_arr = current_dim;
	 }
;

/* Regla donde se definen los tipos de números posibles.
   numero -> signo int | signo double | signo float
   Aquí es desde donde se guarda el tipo del número hasta llegar a exp. También se
   define el valor de este número en cadena. */
numero:
	signo int { $$.type = $2.type; strcpy($$.val, $1); strcat($$.val, $2.val); }
	| signo double { $$.type = $2.type; strcpy($$.val, $1); strcat($$.val, $2.val); }
	| signo float { $$.type = $2.type; strcpy($$.val, $1); strcat($$.val, $2.val); }
;

/* Los signos de los números
   signo -> plus | minus | ɛ */
signo: 
	 plus { strcpy($$,""); }
	 | minus { strcpy($$, "-"); }
	 | %empty { strcpy($$,""); }
;

/* Aquí se definen las dimensiones de los arreglos.
   arreglo -> [numero] arreglo | ɛ */
arreglo:
    lbracket numero rbracket arreglo {
        /* Obtenemos el las dimenciones del arreglo hijo y le agregamos el de la actual
            dimensión. */
        if ($2.type != 0) {
            yyerror("te pasaste de verga. mete tu entero!");
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
        renglon.base.smt = null;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);
        current_arr_type = stack_masterchefs->tabla->tt->count-1;
    } 
    | %empty { $$.tam = 0; }
;

/* Definiciones de las funciones
   funcs -> func tipo id (args) { decls sents } funcs | ɛ
   Se agrega la función a la tabla de simbolos global con sus argumentos */
funcs:
	 func tipo id {
	    /* Creamos el mastertab de la función y la agregamos a la pila de mastertabs
	       ya que decls agrega sus declaraciones al tope de la pila y queremos que se agreguen
	       al mastertab de la función. */
		struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
		ntab->tt = (typetab *) malloc(sizeof(typetab));
		ntab->st = (symtab *) malloc(sizeof(symtab));
		create_table(ntab->st);
		create_type_table(ntab->tt);
		stack_masterchefs = mete(stack_masterchefs, ntab);
		current_function_type = $2.type;
	 }
	 lpar args rpar {
	    /* Agregamos una etiqueta que nos diga donde está el código de la función. */
		cuadrupla c;
		c.op = label;
		char lab[32];
		strcpy(lab, newlabel());
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, $3);
		insert_cuad(&codigo_intermedio, c);

        /* Agregamos la función a la tabla de simbolos global junto con los tipos de los argumentos. */
	 	sym s;
		strcpy(s.id, $3);
		s.type = $2.type;
		s.dir = masterchef->tt->count;
		s.var = 1;
		for(int j = 0; j < $6.num; j++){
			s.args[j] = $6.lista_args[j];
		}
		s.num_args = $6.num;
		insert(masterchef->st, s);
	 }
	 lcurlyb decls sents {
	    /* Aquí se hace backpatch para que se actualicen las etiquetas. */
        cuadrupla c;
        char label[32];
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$11));
        insert_cuad(&codigo_intermedio, c);                
        strcpy(label, newlabel());                                                
        backpatch(&$11, label, &codigo_intermedio);
	 }
	 rcurlyb {
		struct mastertab* sacada;
		sacada = tope(stack_masterchefs); 
		stack_masterchefs = saca(stack_masterchefs);

        /* Agregamos la referencia del masterchef de la función */
		typerow renglon;
		renglon.type = 7;
		renglon.tam = $10.cantidad;
		renglon.base.renglon = -2;
		renglon.base.smt = sacada;
		insert_type_table(stack_masterchefs->tabla->tt, renglon);

		cuadrupla c;
		char label2[32];
		strcpy(label2, newlabel());
		c.op = goto;
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, label2);
        insert_cuad(&codigo_intermedio, c);                
	 } funcs 
	 | %empty 
;

/* Argumentos de las funciones.
   args -> lista_args | ɛ */
args:
	lista_args {
	    $$.num = $1.num; 
        /* Copiamos los argumentos en que tiene el hijo lista_args. */
        for(int i = 0; i < $1.num; i++){
            $$.lista_args[i] = $1.lista_args[i];
        }
    }
	| %empty { $$.num = 0; }
;

/* Lista de argumentos de las funciones.
   lista_args -> lista_args, tipo id parte_arr | tipo id parte_arr */
lista_args:
    lista_args comma tipo id parte_arr  {
        /* Agregamos a la tabla de simbolos y tipos el argumento de la función */
        typerow renglon;
        renglon.type = $3.type;
        renglon.tam = $3.type;
        renglon.base.renglon = $3.type;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);
        
        sym s;
        strcpy(s.id, $4);
        s.type = $3.type;
        s.dir = dir;
        dir+= renglon.tam;
        insert(stack_masterchefs->tabla->st, s);

        /* Aumentamos el número de argumentos que llevamos guardados. */
        $$.num = 1 + $1.num;
        for(int i = 0; i < $1.num; i++){
            $$.lista_args[i] = $1.lista_args[i];
        }
        $$.lista_args[$$.num-1] = $3.type;
        } 
        | tipo id parte_arr {
        /* Ponemos los casos base de la lista de argumentos y del número de argumentos */
        $$.num = 1;
        $$.lista_args[0] = $1.type;
        
        /* Agregamos a la tabla de simbolos y tipos el argumento de la función */
        typerow renglon;
        renglon.type = $1.type;
        renglon.tam = $1.type;
        renglon.base.renglon = $1.type;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);
    
        print_type_table(stack_masterchefs->tabla->tt);
        sym s;
        strcpy(s.id, $2);
        //s.type = stack_masterchefs->tabla->tt->count-1;
        s.type = $1.type;
        s.dir = dir;
        dir+= renglon.tam;
        insert(stack_masterchefs->tabla->st, s);

        print_table(stack_masterchefs->tabla->st);
    }
;

/* La parte que hace que una variable sea un arreglo
   parte_arr -> [] parte_arr | ɛ */
parte_arr:
        lbracket rbracket parte_arr 
        | %empty 
;

/* Concatenación de sentencias
   sent -> sents sent | sent */
sents:
	sents {
	    /* Creamos una etiqueta */
        cuadrupla c;
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$1));
        insert_cuad(&codigo_intermedio, c);                                
    }
    sent {
	    /* Hacemos Backbatch */
        char label[32];
        strcpy(label, newlabel());                                
        $$ = $3;                
        backpatch(&$1, label, &codigo_intermedio);                
        printf("ss->ss s\n");
    } 
    | sent {
	    /* Hacemos Backbatch */
        char label[32];
        strcpy(label, newlabel());
        $$ = $1;
        backpatch(&$1, label, &codigo_intermedio);
        printf("ss->s\n");
    }
;

/* Todas las posibles sentencias
   sent -> if (cond) sent sentp
         | while (cond) sent
         | do sent while (cond);
         | for (assign; cond; assign)  sent 
         | return exp;
         | return;
         | {sents}
         | switch(exp) {casos}
         | break;
         | print exp;
         | assign;     */
sent:
	if lpar cond rpar {
	    /* Obtenemos la etiqueta que está en el tope de trues de la condición y la agregamos
	       a nuestro código */
        cuadrupla c;
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$3.trues));
        insert_cuad(&codigo_intermedio, c);
    }
    sent {
        /* Agregamos a los falses globales la primer etiqueta que tenemos en la condición.
           Además agregamos a nuestro código el goto que tenemos en el tope de sent */
        cuadrupla c, c1;
        c.op = goto;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$6));
        push_label(&lfalses, get_first(&$3.falses));
        insert_cuad(&codigo_intermedio, c);
    } sentp {
        /* Verificamos si tenemos un else en sentp y hacemos backpatch en ambos casos */
        char label[32];
        strcpy(label, newlabel());
        
        if($8.ifelse==false){
            $$ = merge(&$3.falses, &$8.siguientes);
            backpatch(&$3.falses, label, &codigo_intermedio);                                
            printf("s->if(b) s\n");
        }else{
            char label2[32];                                    
            strcpy(label2, newlabel());                
            $$ = merge(&$6,&$8.siguientes);
            backpatch(&$3.trues, label, &codigo_intermedio);
            backpatch(&$3.falses, label2, &codigo_intermedio);                 
            printf("s->if(b)s else s\n");
        }
    }
    | while  lpar cond rpar { breakeablecitos += 1; } sent {
        /* Creamos nuevas etiquetas que las agregaremos a los trues y falses de cond.  */
        char label[32], label2[32], temp[32];
        strcpy(label, newindex());                
        strcpy(label2, newindex());         
        strcpy(temp, newtemp());
        $$ = $3.falses;
        cuadrupla c1;
        c1.op = iff;
        /* Agregamos un goto para que evalue la condición otra vez */
        strcpy(c1.op2, "goto");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        /* Hacemos backpatch */
        backpatch(&$3.trues, label, &codigo_intermedio);
        backpatch(&$3.falses, label2, &codigo_intermedio);
        printf("s->while(b)s\n");
		breakeablecitos -= 1;
    }
    | do { breakeablecitos += 1; } sent while lpar cond rpar semicolon {
        /* Muy parecido al while */
		char label[32], label2[32], temp[32];
        strcpy(label, newindex());                

		/* Ejecución incondicional de la sentencia */
		backpatch(&$6.trues, label, &codigo_intermedio);

        strcpy(label2, newindex());         
        strcpy(temp, newtemp());
        $$ = $6.falses;
        cuadrupla c1;
        c1.op = iff;
        strcpy(c1.op2, "goto");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&$6.trues, label, &codigo_intermedio);
        backpatch(&$6.falses, label2, &codigo_intermedio);
        printf("s->do s while(b)\n");
		breakeablecitos -= 1;
	}
    | for lpar assign semicolon cond semicolon assign rpar { breakeablecitos += 1; } sent {
        /* Muy parecido al while */
		meter_assign($3.arr_codigo, $3.count_codigo);
        char label[32], label2[32], temp[32];
        strcpy(label, newindex());                
        strcpy(label2, newindex());         
        strcpy(temp, newtemp());
        $$ = $5.falses;
        cuadrupla c1;
        c1.op = iff;
        strcpy(c1.op2, "goto");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&$5.trues, label, &codigo_intermedio);
        backpatch(&$5.falses, label2, &codigo_intermedio);
		meter_assign($7.arr_codigo, $7.count_codigo);
        printf("s->for(ass; cond; ass) sent\n");
		breakeablecitos -= 1;
    }
	| assign semicolon {
	    /* meter_assign ya hace todo el trabajo */
	    meter_assign($1.arr_codigo, $1.count_codigo);
	}
	| return exp semicolon {
        /* Verificamos el tipo de retorno con el de la función */
        if($2.type != current_function_type) {
            yyerror("tipo de retorno distinto al tipo de la funcion \n");
            exit(1);
        }
        /* Agregamos el goto adecuado */
        cuadrupla c1;
        c1.op = goto;
        char label1[32];
        strcpy(label1, newlabel());
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, label1);
        insert_cuad(&codigo_intermedio, c1);
	
	}
	| return semicolon {
        /* Verificamos que el tipo de la función sea void */
        if(4 != current_function_type) {
            yyerror("tipo de retorno void distinto al tipo de la funcion \n");
            exit(1);
        }
    }
	| lcurlyb sents rcurlyb {
        /* Aquí es donde se hace la concatenación de sentencias */
        char label[32];
        $$ = $2;                
        strcpy(label, newlabel());                
        /* Se hace backpatch */
        backpatch(&$2, label, &codigo_intermedio);                                
        printf("s->{ss}\n");
    }  
	| switch lpar exp rpar lcurlyb casos rcurlyb 
	| break semicolon {
        /* Verificamos que el break sea dentro de un break */
	    if(breakeablecitos < 1) {
            yyerror("el break debe estar dentro de un ciclo \n");
            exit(1);
        }
        cuadrupla c1;
        c1.op = goto;
        char label1[32];
        strcpy(label1, newlabel());
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, label1);
        insert_cuad(&codigo_intermedio, c1);

	}
    | print exp semicolon {
        char i[32];
        strcpy(i, newindex());
        $$ = create_list(i);
        printf("s->print(e);\n");
    }
;

/* Asignaciones
   assign -> parte_izq assig exp */
assign: 
    parte_izq assig exp {
        char i[32];
        strcpy(i, newindex());
        $$ = create_list(i);
        /* asignacion es lo que hace todo el trabajo */
        exp e = asignacion($1.id1, $1.id2, $3, $1.type); 
        int iterador;
        $$.count_codigo = e.count_codigo;
        for(iterador = 0; iterador < e.count_codigo; iterador++) {
            $$.arr_codigo[iterador] = e.arr_codigo[iterador];
        }
	} 
;

/* Parte del if que incluye o no un else
   sentp -> ɛ | else sent */
sentp:
	{ /* Decimos que no tenemos un else */ $$.ifelse= false;} %prec ifx
	| else {        
	    /* Agregamos la etiqueta que tenemos en los falses al código*/
        cuadrupla c1;
        c1.op = label;
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, pop_label(&lfalses));
        insert_cuad(&codigo_intermedio, c1);
    } 
    sent {
        /* Decimos que tenemos un else */
        $$.ifelse= true;
        $$.siguientes = $3;
    }
;

/* Casos que maneja el switch.
   sentp -> case numero sent casos | default sent | ɛ  */
casos:
    case numero sent casos 
    | default sent 
    | %empty 
;

/* Parte izquierda de una asignación.
   parte_izq -> id | var_arr | id.id 
   parte_izq tiene como atributos los dos posibles ids (Hay 2 cuando queremos obtener
   el atributo dentro de un struct) y el tipo que es una referencia a si tenemos el
   tipo dentro de var_arr o no */
parte_izq:
    id { strcpy($$.id1, $1); strcpy($$.id2,""); $$.type = -1; }
    | var_arr  { strcpy($$.id1, $1.representacion); $$.type = $1.type; }
    | id dot id { strcpy($$.id1, $1); strcpy($$.id2, $3); $$.type = -1; }
;

var_arr:
	   id lbracket exp rbracket { if($3.type != 0) { 
                                    yyerror("debes indexar el arreglo con un entero.\n"); 
                                  }
								  strcpy($$.representacion, $1);
								  strcat($$.representacion, "[");
								  strcat($$.representacion, $3.dir);
								  strcat($$.representacion, "]");
                                  struct nodo* it = stack_masterchefs;
                                  int encontrado = 0;
                                  while(it != null) {
                                    int x = search(it->tabla->st, $1); 
                                    if(x != -1) {
                                        encontrado = 1;
                                        int type_row = it->tabla->st->symbols[x].type;
                                        $$.type = it->tabla->tt->trs[type_row].base.renglon;
                                        if($$.type == -1) {
                                            yyerror("no seas pendejo. mayor cantidad de dimensiones que las definidas");
                                            exit(1);
                                        }
                                        break;
                                    }
                                    it = it->siguiente;
                                  }
                                  if(!encontrado) {
                                    yyerror("el arreglo no fue declarado antes.\n");
                                    exit(1);
                                  } 
                                  $$.tt = it->tabla->tt; }//valor   
       | var_arr lbracket exp rbracket { 
								  strcat($$.representacion, "[");
								  strcat($$.representacion, $3.dir);
								  strcat($$.representacion, "]");
                                  if($3.type != 0) { 
                                    yyerror("debes indexar el arreglo con un entero.\n"); 
                                  }
                                  if($1.type == -1) {
                                    yyerror("no seas pendejo. mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  }  
                                  int row_hijo = $1.type;
                                  $$.type = (*$1.tt).trs[row_hijo].base.renglon;
                                  if($$.type == -1) {
                                    yyerror("no seas pendejo. mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  }  
                                  $$.tt = $1.tt;

       }
;

exp:
   exp plus exp { $$ = suma($1, $3); printf("e -> e + e\n"); }  
   | exp minus exp { $$ = resta($1, $3); printf("e -> e - e\n"); }  
   | exp prod exp { $$ = multiplicacion($1, $3); printf("e -> e * e\n"); } 
   | exp div exp { $$ = division($1, $3); printf("e -> e / e\n"); } 
   | exp mod exp { $$ = modulo($1, $3); printf("e -> e mod e\n"); } 
   | var_arr { $$ = envolver_varr($1); printf("e -> id[e]\n"); }
   | id { $$ = identificador($1); printf("e->id\n"); printf("%s\n",$1); } 
   | cadena { $$ = envolver_cadena($1); printf("e -> cadena\n"); }
   | numero { $$ = get_numero($1); printf("e->numero\n"); printf("%s\n",$1.val); }
   | caracter { $$ = envolver_caracter($1); printf("e -> caracter\n"); }
   | id lpar params rpar {
   		verifica_call($1, $3.lista_tipos, $3.count);	
		char temp[32];
		strcpy(temp, newtemp());
		cuadrupla c;
		c.op = call;
		strcpy(c.op1, $1);
		sprintf(c.op2, "%d", $3.count);
		strcpy(c.res, temp);
		insert_cuad(&codigo_intermedio, c);                    
		strcpy($$.dir, temp);
   }
;

params:
	  lista_param {
	  		$$.p = $1.p;
			int i;
			for (i = 0; i < $1.count; i++) {
				$$.lista_tipos[i] = $1.lista_tipos[i];
			}
			$$.count = $1.count;
	  }
	  | %empty { $$.p = 0; $$.count = 0; }
;

lista_param:
		   lista_param comma exp {
				cuadrupla c;
				c.op = param;
				strcpy(c.op1, "");
				strcpy(c.op2, "");
				strcpy(c.res, $3.dir);
				insert_cuad(&codigo_intermedio, c);                    
				$$.p = $1.p + 1;
				$$.lista_tipos[$1.count] = $3.type;
				$$.count = $1.count + 1;
		   }
   		   | exp {
				cuadrupla c;
				c.op = param;
				strcpy(c.op1, "");
				strcpy(c.op2, "");
				strcpy(c.res, $1.dir);
				insert_cuad(&codigo_intermedio, c);                    
				$$.p = 1;
				$$.lista_tipos[0] = $1.type;
				$$.count = 1;
		   }
;

cond:
	cond or {
        cuadrupla c;
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$1.falses));
        insert_cuad(&codigo_intermedio, c);                    
    } cond { 
        char label[32];
        strcpy(label, newlabel());
        backpatch(&$1.falses, label, &codigo_intermedio);
        $$.trues = merge(&$1.trues, &$4.trues);
        $$.falses = $4.falses;
        printf("b -> b || b\n");
    }
    | cond and {
        cuadrupla c;
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$1.trues));
        insert_cuad(&codigo_intermedio, c);                    
    } cond {
        char label[32];
        strcpy(label, newlabel());                        
        $$.falses = merge(&$1.falses, &$4.falses);
        $$.trues = $4.trues;
        backpatch(&$1.trues, label, &codigo_intermedio);
        printf("b -> b && b\n");
    }
    | not cond {
        $$.falses = $2.trues;
        $$.trues = $2.falses;
        printf("b -> !b\n");
    }
    | lpar cond rpar {
        $$.trues = $2.trues;
        $$.falses = $2.falses;
        //strcpy($$.dir, $2.dir);
        printf("b->(b)\n");
    }
    | exp rel exp {
        char i[32];
        char i2[32];
        char temp[32];
        strcpy(i, newindex());
        strcpy(i2, newindex());
        strcpy(temp, newtemp());
        //strcpy($$.dir, temp);
        $$.trues = create_list(i);
        $$.falses = create_list(i2);
        cuadrupla c, c1, c2;
        c.op = $2 ;
        strcpy(c.op1, $1.dir);
        strcpy(c.op2, $3.dir);
        strcpy(c.res, temp);            
        
        c1.op = iff;
        strcpy(c1.op1, temp);
        strcpy(c1.op2, "goto");
        strcpy(c1.res, i);            
        
        c2.op = goto;
        strcpy(c2.op1, "");
        strcpy(c2.op2, "");
        strcpy(c2.res, i2);
        
        insert_cuad(&codigo_intermedio, c);
        insert_cuad(&codigo_intermedio, c1);
        insert_cuad(&codigo_intermedio, c2);
        printf("b->e rel e\n");
        printf("e1.dir %s rel e2.dir %s\n", $1.dir, $3.dir);
    }
    | true {
        char i[32];
        strcpy(i, newindex());
        $$.trues = create_list(i);
        cuadrupla c;
        c.op = goto;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        insert_cuad(&codigo_intermedio, c);
        printf("b->true\n");
    } 
    | false {
        char i[32];
        strcpy(i, newindex());
        $$.falses = create_list(i);
        cuadrupla c;
        c.op = goto;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        insert_cuad(&codigo_intermedio, c);
        printf("b->false\n");
    } 
;

rel:
   lt { $$ = less_than; printf("r-> <\n"); }
   | gt { $$ = greater_than; printf("r-> >\n"); }
   | leq { $$ = less_or_equal_than; printf("r-> <=\n"); }
   | geq { $$ = greater_or_equal_than; printf("r-> >=\n"); }
   | neq { $$ = not_equals; printf("r-> !=\n"); }
   | eq { $$ = equals; printf("r-> ==\n"); } 
;
		
%%

void init(){    
	masterchef = (struct mastertab *) malloc(sizeof(struct mastertab));
	masterchef->tt = (typetab *) malloc(sizeof(typetab));
	masterchef->st = (symtab *) malloc(sizeof(symtab));
	stack_masterchefs = (struct nodo*) malloc(sizeof(struct nodo));
	stack_masterchefs = null;
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

void verifica_call(char id[], int params[], int params_count) {
	int renglon = search(masterchef->st, id);
	if (renglon == -1) {
		yyerror("La funcion que quieres llamra no ha sido declarado\n");
		exit(1);
	}
	if (masterchef->st->symbols[renglon].num_args != params_count) {
		char error[1000];
		strcpy(error, "El número de argumentos con la que fue llamada la función es incorrecto: ");
		yyerror2(error, id);
		exit(1);
	}
	for (int j = 0; j < params_count; j++) {
		if (masterchef->st->symbols[renglon].args[j] != params[j]) {
			char error[1000];
			strcpy(error, "Los tipos de los argumentos que ingresaste no son correcto con la funcion: ");
			yyerror2(error, id);
			exit(1);
		}
	}
	
}

exp asignacion(char *id, char *id2, exp e, int trecibido){
	exp e1;
	printf("asignaciooon\n");
	e1.count_codigo = 0;
	if(trecibido == -1) {
		printf("moco\n");
		int tipo;
		int es_estruct = 0;
		if(strcmp(id2, "") == 0) {
			printf("id2 fue vacio\n");
			tipo = get_tipo_tablas(id);
			printf("%dtipin\n", tipo);
		} else {
			printf("pedro\n");
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
			printf("ichi\n");
			e1.type = e.type;
			printf("dlkeldkelkdlek\n");
			strcpy(e1.dir, id);
			printf("dlkeldkelkdlek\n");
			cuadrupla c;
			c.op = ASSIGNATION;
			printf("o\n");
			printf("%s %d %d\n", e.dir, tipo, e.type);
			strcpy(c.op1, reducir(e.dir, tipo, e.type));
			printf("o\n");
			strcpy(c.op2, "");
			if(es_estruct == 1) {
				char id_con_punto[65];
				strcpy(id_con_punto, id);
				strcat(id_con_punto, ".");
				strcat(id_con_punto, id2);
				strcpy(c.res, id_con_punto);
			} else {
				printf("llega\n");
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
	printf("Asignacion inconsistente krnal\n");
	exit(1);
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
