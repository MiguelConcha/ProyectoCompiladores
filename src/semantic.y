/* 
 * Archivo: semantic.y
 * Authors: Concha Vázquez Miguel
 *             Flores Martínez Andrés
 *             Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *            Vázquez Salcedo Eduardo Eder
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

    /*Archivo para gaurdar los errores*/
    FILE * errores_sintacticos;

    /*Variable auxilir para detectar si el programa tuvo errores*/
    int hay_error = 0;

    /* Funciones para escribir errores */
    void yyerror(char *);
    void yyerror2(char*, char*);

    /* Última función que se ejecutara. */
    void finish();

    /* Variable para el conteo de direcciones */
    int dir=0;
    char current_label[32];

    /* Variables para guardar el tipo y ancho actual */
    int current_type;
    int current_dim;
    int current_arr_type;
    int current_dim_arr;
    int current_function_type;
    char siguiente_breakable_pila[100][32];
    int siguiente_count = 0;

    /* Variables para contar las temporales, etiquetas e indices */
    int label;
    int temp;
    int indice;
    int breakeablecitos = 0;
    char pila_switch[100][32];
    int count_switch = 0;

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
    void verifica_call(char[], int[][2], int);
    void verificar_main();
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
    int dims;
    int rel;
    char char_signo[1];
    struct {
        int p;
        int lista_tipos[100][2];
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
%type<booleanos> casos
%type<siguientes> sent sents assign 
%type<siguientesp> sentp
%type<pi> parte_izq
%type<char_signo> signo
%type<argu> args lista_args
%type<dims> parte_arr


/* Definimos donde empezará el análisis. */
%start prog

%%

/* Regla de producción inicial.
   prog -> decls funcs */
prog:
    { init(); 
      errores_sintacticos = fopen("errores.txt", "w");
    } 
    decls 
    funcs   
    {
        fclose(errores_sintacticos);
        if(hay_error) {
            printf("El programa tiene errores sintacticos\n");
        } else {
            finish();
        }
    }
;

/* Regla donde están todas las declaraciones de variables.
   decls -> tipo lista; decls | ɛ
   En las decls vamos actualizando el tipo actual para heredarlo a lista ya que ahí
   se agrega a la tabla de símbolos. */
decls:
     tipo { 
         current_type = $1.type;
        if($1.type == 4) {
            yyerror("No puedes declarar variables tipo void\n");
            
        }
        current_dim = $1.bytes;
        current_dim_arr = current_dim; 
        current_arr_type = current_type;
     } 
     lista SEMICOLON decls {$$.cantidad = $3.cantidad; $$.cantidad += $5.cantidad; } /*no estamos seguros*/
     | /* empty */ { $$.cantidad = 0; }
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
    signo INT { $$.type = $2.type; strcpy($$.val, $1); strcat($$.val, $2.val); }
    | signo DOUBLE { $$.type = $2.type; strcpy($$.val, $1); strcat($$.val, $2.val); }
    | signo FLOAT { $$.type = $2.type; strcpy($$.val, $1); strcat($$.val, $2.val); }
;

/* Los signos de los números
   signo -> plus | minus | ɛ */
signo: 
     PLUS { strcpy($$,""); }
     | MINUS { strcpy($$, "-"); }
     | /* empty */ { strcpy($$,""); }
;

/* Aquí se definen las dimensiones de los arreglos.
   arreglo -> [numero] arreglo | ɛ */
arreglo:
    LBRACKET numero RBRACKET arreglo {
        /* Obtenemos el las dimenciones del arreglo hijo y le agregamos el de la actual
            dimensión. */
        if ($2.type != 0) {
            yyerror("El número para declarar en el arreglo debe ser entero.");
            
        }
        if ($2.val[0] == '-') {
            yyerror("Error: No se puede declarar dimensión negativa.");
            
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
    | /* empty */ { $$.tam = 0; }
;

/* Definiciones de las funciones
   funcs -> func tipo id (args) { decls sents } funcs | ɛ
   Se agrega la función a la tabla de simbolos global con sus argumentos */
funcs:
     FUNC tipo ID {
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
     LPAR args RPAR {
        /* Agregamos una etiqueta que nos diga donde está el código de la función. */
        cuadrupla c;
        c.op = LABEL;
        char lab[32];
        strcpy(lab, newLabel());
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
            s.args[j][0] = $6.lista_args[j][0];
            s.args[j][1] = $6.lista_args[j][1];
        }
        s.num_args = $6.num;
        insert(masterchef->st, s);
     }
     LCURLYB decls sents {
        /* Aquí se hace backpatch para que se actualicen las etiquetas. */
        cuadrupla c;
        char label[32];
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$11));
        insert_cuad(&codigo_intermedio, c);                
        strcpy(label, newLabel());                                                
        backpatch(&$11, label, &codigo_intermedio);
     }
     RCURLYB {
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
        strcpy(label2, newLabel());
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, label2);
        //insert_cuad(&codigo_intermedio, c);                
     } funcs 
     | /* empty */ 
;

/* Argumentos de las funciones.
   args -> lista_args | ɛ */
args:
    lista_args {
        $$.num = $1.num; 
        /* Copiamos los argumentos en que tiene el hijo lista_args. */
		for(int i = 0; i < $1.num; i++){
			$$.lista_args[i][0] = $1.lista_args[i][0];
			$$.lista_args[i][1] = $1.lista_args[i][1];
		}
    }
    | /* empty */ { $$.num = 0; }
;

/* Lista de argumentos de las funciones.
   lista_args -> lista_args, tipo id parte_arr | tipo id parte_arr */
lista_args:
	lista_args COMMA tipo ID parte_arr  {
		if($3.type == 4) {
			yyerror("Los argumentos no pueden ser tipo void\n");
			
		}
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
			$$.lista_args[i][0] = $1.lista_args[i][0];
			$$.lista_args[i][1] = $1.lista_args[i][1];
		}
		$$.lista_args[$$.num-1][0] = $3.type;
		$$.lista_args[$$.num-1][1] = $5;
	} 
	| tipo ID parte_arr {
		if($1.type == 4) {
			yyerror("Los argumentos no pueden ser tipo void\n");
			
		}
        /* Ponemos los casos base de la lista de argumentos y del número de argumentos */
		$$.num = 1;
		$$.lista_args[0][0] = $1.type;
		$$.lista_args[0][1] = $3;
		
		typerow renglon;
		renglon.type = $1.type;
		renglon.tam = $1.type;
		renglon.base.renglon = $1.type;
		insert_type_table(stack_masterchefs->tabla->tt, renglon);
	
		sym s;
		strcpy(s.id, $2);
		s.type = $1.type;
		s.dir = dir;
		dir+= renglon.tam;
		insert(stack_masterchefs->tabla->st, s);

	}
;

/* La parte que hace que una variable sea un arreglo
   parte_arr -> [] parte_arr | ɛ */
parte_arr:
    LBRACKET RBRACKET parte_arr { $$ = $3 + 1; }
    | /* empty */ { $$ = 0; }
;

/* Concatenación de sentencias
   sent -> sents sent | sent */
sents:
    sents {
        /* Creamos una etiqueta */
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$1));
        insert_cuad(&codigo_intermedio, c);                                
    }
    sent {
        /* Hacemos Backbatch */
        char label[32];
        strcpy(label, newLabel());                                
        $$ = $3;                
        backpatch(&$1, label, &codigo_intermedio);                
        //printf("ss->ss s\n");
    } 
    | sent {
        /* Hacemos Backbatch */
        char label[32];
        strcpy(label, newLabel());
        $$ = $1;
        backpatch(&$1, label, &codigo_intermedio);
        //printf("ss->s\n");
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
    IF LPAR cond RPAR {
        /* Obtenemos la etiqueta que está en el tope de trues de la condición y la agregamos
           a nuestro código */
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$3.trues));
        insert_cuad(&codigo_intermedio, c);
    }
    sent {
        /* Agregamos a los falses globales la primer etiqueta que tenemos en la condición.
           Además agregamos a nuestro código el goto que tenemos en el tope de sent */
        cuadrupla c, c1;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$6));
        push_label(&lfalses, get_first(&$3.falses));
        insert_cuad(&codigo_intermedio, c);
    } sentp {
        /* Verificamos si tenemos un else en sentp y hacemos backpatch en ambos casos */
        char label[32];
        strcpy(label, newLabel());
        
        if($8.ifelse==false){
            $$ = merge(&$3.falses, &$8.siguientes);
            backpatch(&$3.falses, label, &codigo_intermedio);                                
            printf("s->if(b) s\n");
        }else{
            char label2[32];                                    
            strcpy(label2, newLabel());                
            $$ = merge(&$6,&$8.siguientes);
            backpatch(&$3.trues, label, &codigo_intermedio);
            backpatch(&$3.falses, label2, &codigo_intermedio);                 
            printf("s->if(b)s else s\n");
        }
    }
    | WHILE  LPAR cond RPAR {
        /* Creamos nuevas etiquetas que las agregaremos a los trues y falses de cond.  */
        breakeablecitos += 1;
        strcpy(siguiente_breakable_pila[siguiente_count], $<siguientes>$.label[0]);
        siguiente_count++;
    } sent {
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                
        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        $$ = $3.falses;
        cuadrupla c1;
        c1.op = IFF;
        /* Agregamos un goto para que evalue la condición otra vez */
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        /* Hacemos backpatch */
        backpatch(&$3.trues, label, &codigo_intermedio);
        backpatch(&$3.falses, label2, &codigo_intermedio);
        printf("S->while(B)S\n");
        breakeablecitos -= 1; 
        strcpy(siguiente_breakable_pila[siguiente_count], $<siguientes>$.label[0]);
        siguiente_count--;
    }
    | DO {
        /* Muy parecido al while */
        breakeablecitos += 1;
        strcpy(siguiente_breakable_pila[siguiente_count], $<siguientes>$.label[0]);
        siguiente_count++;
    } sent WHILE LPAR cond RPAR SEMICOLON {
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                

        /* Ejecución incondicional de la sentencia */
        backpatch(&$6.trues, label, &codigo_intermedio);

        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        $$ = $6.falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&$6.trues, label, &codigo_intermedio);
        backpatch(&$6.falses, label2, &codigo_intermedio);
        //printf("s->do s while(b)\n");
        breakeablecitos -= 1;
        siguiente_count++;
    }
    | FOR LPAR assign SEMICOLON cond SEMICOLON assign RPAR { 
        /* Muy parecido al while */
        breakeablecitos += 1; 
        strcpy(siguiente_breakable_pila[siguiente_count], $<siguientes>$.label[0]);
        siguiente_count++;
    } sent {
        meter_assign($3.arr_codigo, $3.count_codigo);
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                
        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        $$ = $5.falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&$5.trues, label, &codigo_intermedio);
        backpatch(&$5.falses, label2, &codigo_intermedio);
        meter_assign($7.arr_codigo, $7.count_codigo);
        //printf("s->for(ass; cond; ass) sent\n");
        breakeablecitos -= 1;
        siguiente_count--;
    }
    | assign SEMICOLON {
        /* meter_assign ya hace todo el trabajo */
        meter_assign($1.arr_codigo, $1.count_codigo);
    }
    | RETURN exp SEMICOLON {
        /* Verificamos el tipo de retorno con el de la función */
        if($2.type != current_function_type) {
            yyerror("tipo de retorno distinto al tipo de la funcion \n");
            
        }
        /* Agregamos el goto adecuado */
        cuadrupla c1;
        c1.op = GOTO;
        char label1[32];
        strcpy(label1, newLabel());
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, label1);
        insert_cuad(&codigo_intermedio, c1);
    
    }
    | RETURN SEMICOLON {
        /* Verificamos que el tipo de la función sea void */
        if(4 != current_function_type) {
            yyerror("tipo de retorno void distinto al tipo de la funcion \n");
        }
        cuadrupla c1;
        c1.op = GOTO;
        char label1[32];
        strcpy(label1, newLabel());
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, label1);
        insert_cuad(&codigo_intermedio, c1);    
    }
    | LCURLYB sents RCURLYB {
        /* Aquí es donde se hace la concatenación de sentencias */
        char label[32];
        $$ = $2;                
        strcpy(label, newLabel());                
        /* Se hace backpatch */
        backpatch(&$2, label, &codigo_intermedio);                                
        //printf("s->{ss}\n");
    }  
    | SWITCH LPAR exp RPAR {
		if($3.type != 0) {
			yyerror("La expresion del switch debe ser un numero entero\n");
			
		}
		breakeablecitos++;
		strcpy(siguiente_breakable_pila[siguiente_count], $<siguientes>$.label[0]);
		siguiente_count++;
    
		strcpy(pila_switch[count_switch], $3.dir); count_switch++; 
	} LCURLYB casos RCURLYB {
		count_switch--;
		breakeablecitos--;
		siguiente_count--;
	}
    | BREAK SEMICOLON {
        /* Verificamos que el break sea dentro de un break */
		if(breakeablecitos < 1) {
			yyerror("El break debe estar dentro de un ciclo \n");
			
		}
		cuadrupla c1;
		c1.op = GOTO;
		char label1[32];
		strcpy(label1, newLabel());//siguiente_breakable_pila[siguiente_count]);
		strcpy(c1.op1, "");
		strcpy(c1.op2, "");
		strcpy(c1.res, label1);
		insert_cuad(&codigo_intermedio, c1);

    }
    | PRINT exp SEMICOLON {
        char i[32];
        strcpy(i, newIndex());
        $$ = create_list(i);
        //printf("s->print(e);\n");
    }
;

/* Asignaciones
   assign -> parte_izq assig exp */
assign: 
	parte_izq ASSIG exp {
		char i[32];
		strcpy(i, newIndex());
		$$ = create_list(i);
		/* asignacion es lo que hace todo el trabajo */
		exp e = asignacion($1.id1, $1.id2, $3, $1.type); 
		//printf("S->parte_izq = E;\n");
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
    { /* Decimos que no tenemos un else */ $$.ifelse= false;} %prec IFX
    | ELSE {        
        /* Agregamos la etiqueta que tenemos en los falses al código*/
        cuadrupla c1;
        c1.op = LABEL;
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
    CASE numero { 
        char i[32];
        char i2[32];
        char temp[32];
        strcpy(i, newIndex());
        strcpy(i2, newIndex());
        strcpy(temp, newTemp());
        strcpy(current_label, i2);

        $<booleanos>$.trues = create_list(i);
        $<booleanos>$.falses = create_list(i2);

        cuadrupla c, c1, c2;
        c.op = EQUALS;
        char tope_dir[32];
        strcpy(tope_dir, pila_switch[count_switch-1]);
        strcpy(c.op1, tope_dir);
        strcpy(c.op2, $2.val);
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
        //printf("B-> case num: sent \n");

        cuadrupla c3;
        c3.op = LABEL;
        strcpy(c3.op1, "");
        strcpy(c3.op2, "");
        strcpy(c3.res, i);
        insert_cuad(&codigo_intermedio, c3);
    } sent {
        cuadrupla c, c1;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, current_label);
        push_label(&lfalses, get_first(&$<booleanos>$.falses));
        insert_cuad(&codigo_intermedio, c);

     }
     casos {}
     | DEFAULT sent {} 
     | /* empty */ {}
;

/* Parte izquierda de una asignación.
   parte_izq -> id | var_arr | id.id 
   parte_izq tiene como atributos los dos posibles ids (Hay 2 cuando queremos obtener
   el atributo dentro de un struct) y el tipo que es una referencia a si tenemos el
   tipo dentro de var_arr o no */
parte_izq:
    ID { strcpy($$.id1, $1); strcpy($$.id2,""); $$.type = -1; }
    | var_arr  { strcpy($$.id1, $1.representacion); $$.type = $1.type; }
    | ID DOT ID { strcpy($$.id1, $1); strcpy($$.id2, $3); $$.type = -1; }
;

/* Reglas de producción para la parte izquierda de una asignación cuando es del tipo
   var_arr -> id[exp] */
var_arr:
	ID LBRACKET exp RBRACKET {
        // Verificando que se indexe el arreglo con una expresión de tipo entera.
	    if($3.type != 0) { 
			yyerror("Debes indexar el arreglo con un entero.\n"); 
		}
		if($3.dir[0] != 't' && $3.dir[0] == '-') {
			yyerror("No puedes indexar el arreglo con un arreglo con un número negativo");
		}
		// Formando la cadena que representa a la variable de arreglo indexada.
		strcpy($$.representacion, $1);
		strcat($$.representacion, "[");
		strcat($$.representacion, $3.dir);
		strcat($$.representacion, "]");
        // Creando un nuevo nodo para iterar la pila de tablas maestras.
		struct nodo* it = stack_masterchefs;
        // Recorremos la pila para buscar el identificador en ella.
		int encontrado = 0;
			
		while(it != NULL) {
			// Estamos buscando con el identificador en la tabla de símbolos a la que apunta el iterador.
			int x = search(it->tabla->st, $1); 
			if(x != -1) {
				// Si ya la encontramos, podemos consultar el tipo en dicho renglón encontrado.
				encontrado = 1;
				int type_row = it->tabla->st->symbols[x].type;
				$$.type = it->tabla->tt->trs[type_row].base.renglon;
				$$.tipo_basico = $$.type;
				// En el ciclo seguiremos subiendo a partir de los tipos hasta llegar al de la base.
				// Sin embargo, si en algún punto llegaos a ver un -1 es porque estamos indexando a un arreglo
				// que fue declarado con un número menor de dimensiones y reportamos el error. 
				if($$.type == -1) {
					yyerror("Mayor cantidad de dimensiones que las definidas");
					
				}
				$$.tamanios[0] = it->tabla->tt->trs[$$.tipo_basico+1].tam;
				int mydims = 1;
				while($$.tipo_basico > 4){
					$$.tamanios[mydims] = it->tabla->tt->trs[$$.tipo_basico].tam;
					mydims++;
					$$.tipo_basico = it->tabla->tt->trs[$$.tipo_basico].base.renglon;    
				}
				if($3.dir[0] != 't' && $$.tamanios[$$.indice_tamanios] <= atoi($3.dir)) {
					//yyerror("Index out of bounds exception\n");
					
				}
				$$.indice_tamanios++;
				$$.dims = mydims - 1;
				break;
			}
			it = it->siguiente;
		}
        // Si saliendo del ciclo ocurre que el identificador jamás fue encontrado, entonces
        // no había sido declarado antes y reportamos el error.
		if(!encontrado) {
			yyerror("El arreglo no fue declarado antes.\n");
			
		} 
        // Especificando que la tabla de tipos del lado izquierdo es la tabla a la que apunta el iterador. 
		$$.tt = it->tabla->tt; }//valor   
	| var_arr LBRACKET exp RBRACKET { 
		// Regla de producción recursiva para seguir metiendo indexaciones.
		// Armando la representación de la indexación.
		$$.tipo_basico = $1.tipo_basico;
		$$.dims = $1.dims - 1;
		strcat($$.representacion, "[");
		strcat($$.representacion, $3.dir);
		strcat($$.representacion, "]");
		// Checando que se indexe con una expresión de tipo entera.
		if($3.type != 0) { 
			yyerror("Debes indexar el arreglo con un entero.\n"); 
		}
		if($3.dir[0] != 't' && $3.dir[0] == '-') {
            yyerror("No puedes indexar el arreglo con un arreglo con un número negativo");
            
        }
        // Comprobando si se indexó con más dimensiones de aquellas con que fue definido.
		if($1.type == -1) {
			yyerror("Mayor cantidad de dimensiones que las definidas");
			
		}  
        // Checando el tipo del rengón del varr_arr del cuerpo de la producción.
		int row_hijo = $1.type;
		$$.type = (*$1.tt).trs[row_hijo].base.renglon;
        // Comprobando si se indexó con más dimensiones de aquellas con que fue definido.
		if($$.type == -1) {
			yyerror("Mayor cantidad de dimensiones que las definidas");
			
		}  
		if($3.dir[0] != 't' && $$.tamanios[$$.indice_tamanios] <= atoi($3.dir)) {
			yyerror("Index out of bounds exception\n");
			
		}
		$$.indice_tamanios++;

        // La tabla de tipos de la cabecera es la del varr_arr del cuerpo.
		$$.tt = $1.tt;

	}
;

/* Reglas de producción para las expresiones.
   exp -> exp + exp | exp - exp | exp * exp | exp / exp | exp % exp | varr_arr | 
          CADENA | numero | CARACTER | ID(params) */
exp:
    exp PLUS exp { 
        $$ = suma($1, $3); 
        //printf("E -> E + E\n"); 
    }  
    | exp MINUS exp { $$ = resta($1, $3); 
        //printf("E -> E - E\n");
    }  
    | exp PROD exp { 
        $$ = multiplicacion($1, $3); 
        //printf("E -> E * E\n");
    } 
    | exp DIV exp { 
        $$ = division($1, $3); 
        //printf("E -> E / E\n");
    } 
    | exp MOD exp { 
        $$ = modulo($1, $3); 
        //printf("E -> E mod E\n");
    } 
    | var_arr { 
        $$ = envolver_varr($1); 
		$$.tipo_basico = $1.tipo_basico;
		$$.dims = $1.dims;
        //printf("E -> id[E]\n"); 
    }
    | ID { 
        $$ = identificador($1); 
        //printf("E->id\n");
    } 
    | CADENA { 
        // Pasando la cadena de la expresión regular a un tipo expresión.
        $$ = envolver_cadena($1); 
        //printf("E -> CADENA\n"); 
    }
    | numero { 
        $$ = get_numero($1);
        //printf("E->numero\n");
    }
    | CARACTER { 
        // Pasando el carácter de la expresión regular a un tipo expresión.
        $$ = envolver_caracter($1); 
        //printf("E -> CARACTER\n");
    }
    | ID LPAR params RPAR {
        // Verificamos que la llama a la función sea válida 
        // de acuerdo a la lista de tipos con que fue declarada y los tipos de los
        // argumentos.
        verifica_call($1, $3.lista_tipos, $3.count);    
        char temp[32];
        strcpy(temp, newTemp());
        // Creando la cuadrupla para el código.
        cuadrupla c;
        // Es una llamada a función.
        c.op = CALL;
        strcpy(c.op1, $1);
        sprintf(c.op2, "%d", $3.count);
        strcpy(c.res, temp);
        insert_cuad(&codigo_intermedio, c);                    
        strcpy($$.dir, temp);
    }
;

/* Reglas de producción para los parámetros.
   params -> lista_param | ε */
params:
    lista_param {
        // El número de parámetros es el que carga la lista.
        $$.p = $1.p;
        // Copiamos los tipos parámetros de la lista de parámetros.
        int i;
		for (i = 0; i < $1.count; i++) {
			$$.lista_tipos[i][0] = $1.lista_tipos[i][0];
			$$.lista_tipos[i][1] = $1.lista_tipos[i][1];
		}
        // El número de parámetros son los de la lista de parámetros.
        $$.count = $1.count;
    }
    | /* empty */ {
        // Si cae en este caso, el número de parámetros es cero. 
        $$.p = 0; 
        $$.count = 0;
    }
;

/* Reglas de producción para la lista de parámetros.
   lista_param -> lista_param , exp | exp */
lista_param:
	lista_param COMMA exp {
		// Creando la cuadrupla e insertándola en el código intermedio.
		cuadrupla c;
		c.op = PARAM;
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, $3.dir);
		insert_cuad(&codigo_intermedio, c);                    
		// Incrementando la cantidad de argumentos y copiando el tipo del actual.                  
		$$.p = $1.p + 1;
		$$.lista_tipos[$1.count][0] = $3.tipo_basico;
		$$.lista_tipos[$1.count][1] = $3.dims;
		$$.count = $1.count + 1;
	}
		| exp {
		// Creando la cuadrupla e insertándola en el código intermedio.
		cuadrupla c;
		c.op = PARAM;
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, $1.dir);
		insert_cuad(&codigo_intermedio, c);                    
		// Como es el caso base, tenemos un solo argumento y su tipo es el tipo de la expresión.                    
		$$.p = 1;
		$$.lista_tipos[0][0] = $1.tipo_basico;
		$$.lista_tipos[0][1] = $1.dims;
		$$.count = 1;
	}
;

/* Reglas de producción para las condiciones.
   cond -> cond || cond | cond && cond | ! cond | ( cond ) | exp rel exp
           | exp | true | false */
cond:
    cond OR {
        // Creación de la cuadrupla con la operación de label.
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$1.falses));
        // Inserción de la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);                    
    } cond { 
        char label[32];
        strcpy(label, newLabel());
        // Haciendo backpatch con la nueva etiqueta. 
        backpatch(&$1.falses, label, &codigo_intermedio);
        $$.trues = merge(&$1.trues, &$4.trues);
        $$.falses = $4.falses;
        //printf("b -> b || b\n");
    }
    | cond AND {
        // Creación de la cuadrupla con la operación de label.
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&$1.trues));
        // Inserción de la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);                    
    } cond {
        char label[32];
        strcpy(label, newLabel());                        
        $$.falses = merge(&$1.falses, &$4.falses);
        $$.trues = $4.trues;
        // Haciendo backpatch con la nueva etiqueta. 
        backpatch(&$1.trues, label, &codigo_intermedio);
        //printf("b -> b && b\n");
    }
    | NOT cond {
        // Se invierten flases y trues.
        $$.falses = $2.trues;
        $$.trues = $2.falses;
        //printf("b -> !b\n");
    }
    | LPAR cond RPAR {
        // Dependen de los falses y trues de la condución del cuerpo.
        $$.trues = $2.trues;
        $$.falses = $2.falses;
        //printf("B->(B)\n");
    }
    | exp rel exp {
        char i[32];
        char i2[32];
        char temp[32];
        // Crenado dos nuevos índices y un temporal.
        strcpy(i, newIndex());
        strcpy(i2, newIndex());
        strcpy(temp, newTemp());
        $$.trues = create_list(i);
        $$.falses = create_list(i2);
        
        // Creando las cuadruplas.
        cuadrupla c, c1, c2;
        
        // Especificación de la primera cuadrupla.
        c.op = $2 ;
        strcpy(c.op1, $1.dir);
        strcpy(c.op2, $3.dir);
        strcpy(c.res, temp);            
        
        // Especificación de la segunda cuadrupla.
        c1.op = IFF;
        strcpy(c1.op1, temp);
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, i);            
            
        // Especificación de la tercera cuadrupla.
        c2.op = GOTO;
        strcpy(c2.op1, "");
        strcpy(c2.op2, "");
        strcpy(c2.res, i2);
        
        // Insertando cuadruplas para el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        insert_cuad(&codigo_intermedio, c1);
        insert_cuad(&codigo_intermedio, c2);
        //printf("b->e rel e\n");
    }
    | TRUE {
        char i[32];
        strcpy(i, newIndex());
        $$.trues = create_list(i);
        // Creación de la cuadrupla y con la operación de goto.
        cuadrupla c;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        // Inserción de la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        //printf("b->true\n");
    } 
    | FALSE {
        char i[32];
        strcpy(i, newIndex());
        $$.falses = create_list(i);
        // Creación de la cuadrupla y con la operación de goto.
        cuadrupla c;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        // Inserción de la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        //printf("b->false\n");
    } 
;

/* Reglas de producción para los operadores relacionales.
   rel -> < | > | >= | <= | != | == 
   En cada caso basta con establecer el atributo númerico 
   de la cabecera de la producción dependiendo del token devuelto. */
rel:
    LT { 
        $$ = LESS_THAN; 
        //printf("R-> <\n"); 
    }
    | GT { 
        $$ = GREATER_THAN; 
        //printf("R-> >\n");
    }
    | LEQ { 
        $$ = LESS_OR_EQUAL_THAN; 
        //printf("R-> <=\n");
    }
    | GEQ { 
        $$ = GREATER_OR_EQUAL_THAN; 
        //printf("R-> >=\n");
    }
    | NEQ { 
        $$ = NOT_EQUALS;
        //printf("R-> !=\n"); 
    }
    | EQ { 
        $$ = EQUALS; 
        //printf("R-> ==\n");
    } 
;
        
%%

/**
 * Inicializa la tabla maestra que tiene los apuntadores
 * a una tabla de símbolos y a una de tipos.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
void init(){    
    // Reservando memoria dinámicamente para la tabla maestra y sus dos tablas.
    masterchef = (struct mastertab *) malloc(sizeof(struct mastertab));
    masterchef->tt = (typetab *) malloc(sizeof(typetab));
    masterchef->st = (symtab *) malloc(sizeof(symtab));
    stack_masterchefs = (struct nodo*) malloc(sizeof(struct nodo));
    stack_masterchefs = NULL;
    
    // Creando las dos tablas que tendrá como apuntadores.
    create_table(masterchef->st);
    create_type_table(masterchef->tt);

    // Metiéndo la tabla maestra a la pila de las tablas maestras. 
    // Esta que metemos es la tabla del alcance global.
    stack_masterchefs = mete(stack_masterchefs, masterchef);

    // Creamos el contenedor del código intermedio e inicializamos las labels para los falses.
    create_code(&codigo_intermedio);
    create_labels(&lfalses);    
}

/**
 * Función que determina cuál de los dos tipos de los que se pasan 
 * como parámetros (representador por enteros) es mayor que el otro.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
int max(int t1, int t2){
    // Basta con ir checando por casos y en cada tipo regresar el mayor.
    // Esto se debe a que double > float > int y los enteros que los
    // representan son respectivamente 2 > 1 > 0.
    if( t1==t2) return t1;
    if( t1 ==0 && t2 == 1) return 1;
    if( t1 ==1 && t2 == 0) return 1;
    if( t1 ==0 && t2 == 2) return 2;
    if( t1 ==2 && t2 == 0) return 2;
    if( t1 ==2 && t2 == 1) return 2;
    if( t1 ==1 && t2 == 2) return 2;
    // Si no cae en ninguno de los casos anteriores, regresamos -1.
    else return -1;
}

/**
 * Función que genera el código intermedio para la adición de dos
 * números. Devuelve la expresión resultante de la suma de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp suma(exp e1, exp e2){
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    e.tipo_basico = e.type;
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es suma.
        c.op = MAS;
        // Realizando los casts necesarios en el código intermedio generado.
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que genera el código intermedio para la sustracción de dos
 * números. Devuelve la expresión resultante de la resta de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp resta(exp e1, exp e2){
    exp e;
    cuadrupla c;
    char t[32];
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    e.tipo_basico = e.type;
    
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es resta.
        c.op = MENOS;
        // Realizando los casts necesarios en el código intermedio generado.
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que genera el código intermedio para el producto de dos
 * números. Devuelve la expresión resultante de la multiplicación de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp multiplicacion(exp e1, exp e2){
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    e.tipo_basico = e.type;
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es multiplicación.
        c.op = MULTIPLICACION;
        // Realizando los casts necesarios en el código intermedio generado.
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que genera el código intermedio para el cociente de dos
 * números. Devuelve la expresión resultante de la división de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp division(exp e1, exp e2){
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    e.tipo_basico = e.type;
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es división.
        c.op = DIVISION;
        // Realizando los casts necesarios en el código intermedio generado.
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que genera el código intermedio para el módulo de dos
 * números. Devuelve la expresión resultante del módulo de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp modulo(exp e1, exp e2){
    // Para hacer el módulo ambos tipos de las expresiones deben ser enteros.
    if(e1.type != 0 || e2.type != 0) {
        yyerror("Error: La operación módulo requiere operandos enteros.\n");
        
    }
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    e.tipo_basico = e.type;
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es módulo.
        c.op = MODULO;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que busca un identificador en la tabla del tope de la pila
 * de tablas maestras y si no lo encuentra lo busca también en la tabla
 * de símbolos global. Esto sirve para las funciones.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 9 de diciembre de 2018.
 */
int get_tipo_tablas(char *id) {
    int tipo;
    // Buscándolo en la tabla de símbolos del tope.
    int busqueda = search(stack_masterchefs->tabla->st, id);
    if (busqueda == -1) {
        // Si no lo encontramos lo buscamos en la global.
        busqueda = search(masterchef->st, id);
        if (busqueda == -1) {
            // Si no está es porque no fue declarado antes.
            yyerror("Error: El identificador para la variable no fue declarada antes.\n");
            
        } else {    
            // Si sí lo encontramos en la global, obtenemos su tipo.
            tipo = get_type(masterchef->st, id);
        }
    } else {
        // Si lo encontramos en la global, obtenemos su tipo.
        tipo = get_type(stack_masterchefs->tabla->st, id);
    }
    return tipo;
}

/**
 * Función que verifica que la llamada a una función sea válida.
 * Checa que lo que se llama en efecto sea una función, tenga la 
 * misma cantidad de parámetros que los argumentos con que fue 
 * declarada y además los tipos de cada uno coincidan.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 9 de diciembre de 2018.
 */
void verifica_call(char id[], int params[][2], int params_count) {
    // Buscando el renglón en la tabla de símbolos del identificador.
    int renglon = search(masterchef->st, id);
    if (renglon == -1) {
        // Error en caso de que no sea encontrada.
        yyerror("La funcion que quieres llamra no ha sido declarado\n");
        
    }
    // Checando que sea llamda con el mismo número de argumentos con que fue declarada.
    if (masterchef->st->symbols[renglon].num_args != params_count) {
        char error[1000];
        strcpy(error, "El número de argumentos con la que fue llamada la función es incorrecto: ");
        yyerror2(error, id);
        
    }
    // Checando que el tipo de los parámetros con que es llamda coincida con los de la declaración.
    for (int j = 0; j < params_count; j++) {
        if (masterchef->st->symbols[renglon].args[j][0] != params[j][0] || masterchef->st->symbols[renglon].args[j][1] != params[j][1]) {
            char error[1000];
            strcpy(error, "Los tipos de los argumentos que ingresaste no son correcto con la funcion: ");
            yyerror2(error, id);
            
        } 
    }
    
}

/**
 * Función que sirve para generar y llevar a cabo la creación
 * de código itermedio para una asignación del tipo parte_izq = exp . 
 * Recibe como parámetros el identificador de la parte izquierda en dos partes
 * (puede ser id . id y se reciben ambos), la expresión del lado derecho de la expresión
 * y el entero que representa su tipo.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 10 de diciembre de 2018.
 */
exp asignacion(char *id, char *id2, exp e, int trecibido) {
    // La expresión que será devuelta.
    exp e1;
    e1.count_codigo = 0;
    // Cuando no es un var_arr:
    if (trecibido == -1) {
        int tipo = -1;
        int es_estruct = 0;
        // Si no es de la forma id.id, el segundo id es vacío y podemos obtener el tipo del primero.
        if(strcmp(id2, "") == 0) {
            tipo = get_tipo_tablas(id);
        } else {
            // En otro caso, es de la forma id.id, entonces debemos buscar el primer identificador.
            es_estruct = 1;
            // Buscamos el id antes del punto en la tabla de símbolos global para saber si fue declarado antes.
            int renglon = search(masterchef->st, id);
            if(renglon == -1) {
                //Ya que no se encontro el id en la tabla global, lo buscamos en la tabla local
                renglon = search(stack_masterchefs->tabla->st, id);
                if(renglon == -1) {
                    //En caso de que no se encontro en ningun lugar entonces gurdamos el error
                    yyerror("El identificador no fue declarado\n");
                } else {
                    //Se encontro el id en la tabla local, ahora lo buscamos el segundo id en su tabla asociada
                    renglon = stack_masterchefs->tabla->st->symbols[renglon].type;
                    //revisamos que el tipo del id sea un struct
                    if(stack_masterchefs->tabla->tt->trs[renglon].base.renglon != -2) {
                        yyerror("el identificador que buscas no es parte de un struct");
                    } else {
                        //buscamos el segundo id en ls tabla se simbolos de la estructura
                        int renglon2 = search(stack_masterchefs->tabla->tt->trs[renglon].base.smt->st, id2);
                        if(renglon2 == -1) {
                            //lanzamos error si no se encontro el segundo id
                            yyerror("el identidicador que buscas no es parte de un struct");
                        } else {
                            //Encontramos el segundo id, obtenemos su tipo con la tabla de tipos asociada y guardamos su tipo.     
                            renglon2 = stack_masterchefs->tabla->tt->trs[renglon].base.smt->st->symbols[renglon2].type; 
                            tipo = stack_masterchefs->tabla->tt->trs[renglon].base.smt->tt->trs[renglon2].type;
                        }
                    }
                }
            } else {
                //Se encontro el id en la tabla global, ahora lo buscamos el segundo id en su tabla de tipos asociada
                renglon = masterchef->st->symbols[renglon].type;
                //revisamos que el tipo del id sea un struct
                if(masterchef->tt->trs[renglon].base.renglon != -2) {
                    yyerror("el identificador que buscas no es parte de un struct");
                } else {
                    //buscamos el segundo id en ls tabla se simbolos de la estructura
                    int renglon2 = search(masterchef->tt->trs[renglon].base.smt->st, id2);
                    if(renglon2 == -1) {
                        //lanzamos error si no se encontro el segundo id
                        yyerror("el identidicador que buscas no es parte de un struct");
                    } else {
                        //Encontramos el segundo id, por lo que guardamos su tipo.
                        renglon2 = masterchef->tt->trs[renglon].base.smt->st->symbols[renglon2].type;
                        tipo = masterchef->tt->trs[renglon].base.smt->tt->trs[renglon2].type;
                    }
                }
            }
        }    
        if ( tipo != -1) {        
            // El tipo de la expresión a devolver es el de la expresión luego de la asignación.
            e1.type = e.type;
            strcpy(e1.dir, id);
            // Creando la cuadrupla para la asignación y colocando la operación.
            cuadrupla c;
            c.op = ASSIGNATION;
            // Colocando lo necesario de la cuadrupla.
            if(reducir(e.dir, tipo, e.type) != NULL) { 
                strcpy(c.op1, reducir(e.dir, tipo, e.type));
            } else if (ampliar(e.dir, e.type, tipo) != NULL){
                strcpy(c.op1, ampliar(e.dir, e.type, tipo));
            } else {
                yyerror("Asignacion inconsistente de tipos");
            }
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
            // Colocando lo respectivo al código a la expresión.
            e1.arr_codigo[e1.count_codigo] = c;    
            e1.count_codigo++;
        } else {
            // Caso para el error semántico.
            yyerror("El identificador no fue declarado\n"); 
        }
    } else { // Aquí se maneja el caso para var_arr.
        // VARARR
        e1.type = e.type;
        strcpy(e1.dir, id);
        // Creando la cuadrupla.
        cuadrupla c;
        c.op = ASSIGNATION;
        if(reducir(e.dir, trecibido, e.type) != NULL) { 
            strcpy(c.op1, reducir(e.dir, trecibido, e.type));
        } else if (ampliar(e.dir, e.type, trecibido) != NULL) {
            strcpy(c.op1, ampliar(e.dir, e.type, trecibido));
        } else {
                yyerror("Asignacion inconsistente de tipos");
        }
        strcpy(c.op2, "");
        // En este caso id es la representacin de var_arr.
        strcpy(c.res, id);//en este caso id es la representacin de vararr
        // Asociando lo respectivo al código a la expresión.
        e1.arr_codigo[e1.count_codigo] = c;
        e1.count_codigo++;
	}
	return e1;
}

/**
 * Función que copia el valor del número a la dirección de una
 * expresión creada.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
exp get_numero(numero n){
    exp e;
    e.type = n.type;
    e.tipo_basico = e.type;
    strcpy(e.dir, n.val);
    return e;
}

/**
 * Función que copia el valor de una cadena en la dirección
 * de una nueva expresión que es creada.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
exp envolver_cadena(cadena cadenita) {
    exp e;
    e.type = cadenita.type;
    e.tipo_basico = e.type;
    strcpy(e.dir, cadenita.val);
    return e;
}

/**
 * Función que copia el valor de una carácter en la dirección
 * de una nueva expresión que es creada.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
exp envolver_caracter(caracter caractercito) {
    exp e;
    e.type = caractercito.type;
    e.tipo_basico = e.type;
    e.dir[0] = caractercito.val;
    return e;
}

/**
 * Función que copia la representación de un arreglo
 * en la dirección de una expresión que es creada.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
exp envolver_varr(varr arreglito) {
    exp e;
    e.type = arreglito.type;
    strcpy(e.dir, arreglito.representacion);
    return e;
}

/**
 * Función que copia el id en la dirección de una 
 * nueva expresión creada que al final devuelta.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
exp identificador(char *id){
    exp e;
    // Buscamos el identificador en la tabla de símbolos del tipo de la pila.
    if(search(stack_masterchefs->tabla->st, id) !=-1){
        // Si lo encontramos, podemos copiar su valor en la dirección de la expresión.
        e.type = get_type(stack_masterchefs->tabla->st, id);
        e.tipo_basico = e.type;
        int mydims = 0;
        while(e.tipo_basico > 4){
            e.tipo_basico = stack_masterchefs->tabla->tt->trs[e.tipo_basico].base.renglon;    
            mydims++;
        }
        e.dims = mydims;
        strcpy(e.dir, id);
    }else{
        // En otro caso buscamos el identificador en la tabla global.
        if(search(masterchef->st, id) !=-1){
            // Si ya lo encontramos, copiamos su valor en el dirección de la expresión.
            e.type = get_type(masterchef->st, id);
            e.tipo_basico = e.type;
            int mydims = 0;
            while(e.tipo_basico > 4){
                mydims++;
                e.tipo_basico = masterchef->tt->trs[e.tipo_basico].base.renglon;    
            }
            e.dims = mydims;
            strcpy(e.dir, id);
        } else {
            // Si no, entonces error porque no fue declarada antes.
            yyerror("Error: el identificador no existe");
            
        }
    }
    return e;
}

/**
 * Función que genera el código intermedio
 * para los casts necesarios para lost tipos.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
char *ampliar(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    if( t1==t2) return dir;
    // Cast de entero a float.
    if( t1 ==0 && t2 == 1){
        c.op = EQUALS;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        return t;
    }
    // Cast de entero a double.
    if( t1 ==0 && t2 == 2){
        c.op = EQUALS;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        return t;
    }        
    // Cast de float a double.
    if( t1 ==1 && t2 == 2) {
        c.op = EQUALS;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        return t;
    }         
    return NULL;   
}

/**
 * Función que genera el código intermedio
 * para los casts necesarios para lost tipos, cuando
 * el cast es a uno menor.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
char *reducir(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    if( t1==t2) return dir;
    // Cast de float a int.
    if( t1 ==0 && t2 == 1){
        c.op = EQUALS;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un float a un int\n");
        return t;
    }
    // Cast de double a int.
    if( t1 ==0 && t2 == 2){
        c.op = EQUALS;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un int\n");
        return t;
    }        
    // Cast de double a float.
    if( t1 ==1 && t2 == 2) {
        c.op = EQUALS;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un float\n");
        return t;
    }
    return NULL;
}

/**
 * Función que crea un nuevo tempora.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 7 de diciembre de 2018.
 */
char* newTemp(){
    // Reservando memoria dinámicamente para el temporal.
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "t");
    char num[30];
    sprintf(num, "%d", temp);
    strcat(temporal, num);
    temp++;
    return temporal;
}

/**
 * Función que crea un nueva etiqueta.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 7 de diciembre de 2018.
 */
char* newLabel(){
    // Reservando memoria dinámicamente para la etiqueta.
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "L");
    char num[30];
    sprintf(num, "%d", label);
    strcat(temporal, num);
    label++;
    return temporal;
}

/**
 * Función que crea un nuevo índice.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 7 de diciembre de 2018.
 */
char* newIndex(){
    // Reservando memoria dinámicamente para la cadena del índice.
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "I");
    char num[30];
    sprintf(num, "%d", indice);
    strcat(temporal, num);
    indice++;
    return temporal;
}

/**
 * Función que imprime los mensajes de error.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
void yyerror(char *msg) {
    printf("Línea: %d\n%s\n", yylineno, msg);
    hay_error = 1;
    fprintf(errores_sintacticos,"Línea: %d\n%s\n", yylineno, msg);
    exit(1);
}

/**
 * Función que concatena dos cadenas que serán 
 * impresas como el mensaje de error.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
void yyerror2(char *c, char *c2){
    strcat(c, c2);
    yyerror(c);
}

/**
 * Función que imprime el código intermedio
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
void finish(){    
    verificar_main();
    /* Imprimimos las tablas de tipo y símbolos y finalizamos. */
    printf("Tabla de tipos\n");
    print_type_table(masterchef->tt);
    printf("Tabla de simbolos\n");
    print_table(masterchef->st); 
    //printf("P -> D funcs\n");
    print_code(&codigo_intermedio);    
}

/**
 * Función que itera tantas veces como indica el segundo 
 * parámetro de la función y va metiendo el contenido
 * de la cuadrúpla dada como parámetro en el código intermedio.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
void meter_assign(cuadrupla c[], int cou){
    for(int j = 0; j < cou; j++){
        insert_cuad(&codigo_intermedio, c[j]);
    }
}

/**
 * Función que verifica que exista la declaración de la función
 * 'main' y que no haya funciones declaradas después de esta.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 12 de diciembre de 2018.
 */
void verificar_main() {
    // Buscamos la función 'main' en la tabla de símbolos global.
    int renglon = search(masterchef->st, "main");
    // Error en caso de que no se haya declarado.
    if (renglon == -1) {
        yyerror("Error: La función 'main' no fue declarada. ");
        
    }
    // Recorremos desde el renglón en que fue declarada hacia abajo
    // a ver si hay otra función, en cuyo caso habrá un error.
    for (int i = renglon + 1; i < masterchef->st->count; i++) {
        // Verificación de que haya una función.
        if (masterchef->st->symbols[i].var == 1) {
            yyerror("No puedes declarar funciones después del 'main'.");
            
        }
    }
}