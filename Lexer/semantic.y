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
    int current_function_type;

    /* Varaibles para contar las temporales, etiquetas e indices */
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
     FUNC tipo ID {
        struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
        ntab->tt = (typetab *) malloc(sizeof(typetab));
        ntab->st = (symtab *) malloc(sizeof(symtab));
        create_table(ntab->st);
        create_type_table(ntab->tt);
        stack_masterchefs = mete(stack_masterchefs, ntab);
        current_function_type = $2.type;
     }
     LPAR args RPAR {
        cuadrupla c;
        c.op = LABEL;
        char lab[32];
        strcpy(lab, newLabel());
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, $3);
        insert_cuad(&codigo_intermedio, c);

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
     LCURLYB decls sents {
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
        struct mastertab* sacada;// = (struct mastertab *) malloc(sizeof(struct mastertab));
        sacada = tope(stack_masterchefs); 
        stack_masterchefs = saca(stack_masterchefs);

        typerow renglon;
        renglon.type = 7;
        renglon.tam = $10.cantidad;
        renglon.base.renglon = -2;
        renglon.base.smt = sacada;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);
        //$$.type = stack_masterchefs->tabla->tt->count-1; 
        //$$.bytes = $4.cantidad; 
        cuadrupla c;
        char label2[32];
        strcpy(label2, newLabel());
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, label2);
        insert_cuad(&codigo_intermedio, c);                
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
                
            typerow renglon;
            renglon.type = $3.type;
            renglon.tam = $3.type;
            renglon.base.renglon = $3.type;
            insert_type_table(stack_masterchefs->tabla->tt, renglon);
            
            print_type_table(stack_masterchefs->tabla->tt);
            sym s;
            strcpy(s.id, $4);
            //s.type = stack_masterchefs->tabla->tt->count-1;
            s.type = $3.type;
            s.dir = dir;
            dir+= renglon.tam;
            insert(stack_masterchefs->tabla->st, s);

            print_table(stack_masterchefs->tabla->st);
        
        
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
    | WHILE  LPAR cond RPAR { breakeablecitos += 1; } sent {
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
        breakeablecitos -= 1;
    }
    | DO { breakeablecitos += 1; } sent WHILE LPAR cond RPAR SEMICOLON {
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                

        //Ejecucion incondicional de la sentencia
        backpatch(&$6.trues, label, &codigo_intermedio);

        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        printf("tempito %s /n", temp);
        $$ = $6.falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&$6.trues, label, &codigo_intermedio);
        backpatch(&$6.falses, label2, &codigo_intermedio);
        printf("S->do S while(B)\n");
        breakeablecitos -= 1;
    }
    | FOR LPAR assign SEMICOLON cond SEMICOLON assign RPAR { breakeablecitos += 1; } sent {
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
        breakeablecitos -= 1;
    }
    | assign SEMICOLON { meter_assign($1.arr_codigo, $1.count_codigo); }
    | RETURN exp SEMICOLON {
            if($2.type != current_function_type) {
                yyerror("Tipo de retorno distinto al tipo de la funcion \n");
                exit(1);
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
    | RETURN SEMICOLON {
            if(4 != current_function_type) {
                yyerror("Tipo de retorno void distinto al tipo de la funcion \n");
                exit(1);
            }
      }
    | LCURLYB sents RCURLYB {
        char label[32];
        $$ = $2;                
        strcpy(label, newLabel());                
        backpatch(&$2, label, &codigo_intermedio);                                
        printf("S->{SS}\n");
    }  
    | SWITCH LPAR exp RPAR LCURLYB casos RCURLYB 
    | BREAK SEMICOLON { if(breakeablecitos < 1) {
                            yyerror("El break debe estar dentro de un ciclo \n");
                            exit(1);
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
                printf("abajo\n");
                printf("%s, %s, %d\n", $1.id1, $1.id2,$1.type);
                printf("abajo1\n");
                exp e = asignacion($1.id1, $1.id2, $3, $1.type); 
                printf("abajo2\n");
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

/* Reglas de producción para la parte izquierda de una asignación cuando es del tipo
   var_arr -> id[exp] */
var_arr:
       ID LBRACKET exp RBRACKET { 
                                  // Verificando que se indexe el arreglo con una expresión de tipo entera.
                                  if($3.type != 0) { 
                                    yyerror("Error: Debes indexar el arreglo con un entero.\n"); 
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
                                        // En el ciclo seguiremos subiendo a partir de los tipos hasta llegar al de la base.
                                        // Sin embargo, si en algún punto llegaos a ver un -1 es porque estamos indexando a un arreglo
                                        // que fue declarado con un número menor de dimensiones y reportamos el error. 
                                        if($$.type == -1) {
                                            yyerror("Error: Mayor cantidad de dimensiones que las definidas.");
                                            exit(1);
                                        }
                                        break;
                                    }
                                    it = it->siguiente;
                                  }
                                  // Si saliendo del ciclo ocurre que el identificador jamás fue encontrado, entonces
                                  // no había sido declarado antes y reportamos el error.
                                  if(!encontrado) {
                                    yyerror("Error: El arreglo no fue declarado antes.\n");
                                    exit(1);
                                  }
                                  // Especificando que la tabla de tipos del lado izquierdo es la tabla a la que apunta el iterador. 
                                  $$.tt = it->tabla->tt; 
       }  
       | var_arr LBRACKET exp RBRACKET {
                                  // Regla de producción recursiva para seguir metiendo indexaciones.
                                  // Armando la representación de la indexación.
                                  strcat($$.representacion, "[");
                                  strcat($$.representacion, $3.dir);
                                  strcat($$.representacion, "]");
                                  // Checando que se indexe con una expresión de tipo entera.
                                  if($3.type != 0) { 
                                    yyerror("Error: Debes indexar el arreglo con un entero.\n"); 
                                  }
                                  // Comprobando si se indexó con más dimensiones de aquellas con que fue definido.
                                  if($1.type == -1) {
                                    yyerror("Error: Mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  } 
                                  // Checando el tipo del rengón del varr_arr del cuerpo de la producción.
                                  int row_hijo = $1.type;
                                  $$.type = (*$1.tt).trs[row_hijo].base.renglon;
                                  // Comprobando si se indexó con más dimensiones de aquellas con que fue definido.
                                  if($$.type == -1) {
                                    yyerror("Error: Mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  } 
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
                  printf("E -> E + E\n"); 
                }  
   | exp MINUS exp { $$ = resta($1, $3); 
                     printf("E -> E - E\n");
                   }  
   | exp PROD exp { 
                    $$ = multiplicacion($1, $3); 
                    printf("E -> E * E\n");
                  } 
   | exp DIV exp { 
                   $$ = division($1, $3); 
                   printf("E -> E / E\n");
                 } 
   | exp MOD exp { 
                   $$ = modulo($1, $3); 
                   printf("E -> E mod E\n");
                 } 
   | var_arr { 
               $$ = envolver_varr($1); 
               printf("E -> id[E]\n"); 
             }
   | ID { 
          $$ = identificador($1); 
          printf("E->id\n");
          printf("%s\n", $1); 
        } 
   | CADENA { 
              // Pasando la cadena de la expresión regular a un tipo expresión.
              $$ = envolver_cadena($1); 
              printf("E -> CADENA\n"); 
            }
   | numero { 
              $$ = get_numero($1);
              printf("E->numero\n");
              printf("%s\n",$1.val);
            }
   | CARACTER { 
                // Pasando el carácter de la expresión regular a un tipo expresión.
                $$ = envolver_caracter($1); 
                printf("E -> CARACTER\n");
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
                $$.lista_tipos[i] = $1.lista_tipos[i];
            }
            // El número de parámetros son los de la lista de parámetros.
            $$.count = $1.count;
      }
      | %empty {
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
                $$.lista_tipos[$1.count] = $3.type;
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
                $$.lista_tipos[0] = $1.type;
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
        printf("B -> B || B\n");
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
        printf("B -> B && B\n");
    }
    | NOT cond {
        // Se invierten flases y trues.
        $$.falses = $2.trues;
        $$.trues = $2.falses;
        printf("B -> !B\n");
    }
    | LPAR cond RPAR {
        // Dependen de los falses y trues de la condución del cuerpo.
        $$.trues = $2.trues;
        $$.falses = $2.falses;
        printf("B->(B)\n");
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
        printf("B->E rel E\n");
        printf("E1.dir %s rel E2.dir %s\n", $1.dir, $3.dir);
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
        printf("B->true\n");
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
        printf("B->false\n");
    } 
;

/* Reglas de producción para los operadores relacionales.
   rel -> < | > | >= | <= | != | == 
   En cada caso basta con establecer el atributo númerico 
   de la cabecera de la producción dependiendo del token devuelto. */
rel:
   LT { 
        $$ = LESS_THAN; 
        printf("R-> <\n"); 
      }
   | GT { 
          $$ = GREATER_THAN; 
          printf("R-> >\n");
        }
   | LEQ { 
           $$ = LESS_OR_EQUAL_THAN; 
           printf("R-> <=\n");
         }
   | GEQ { 
           $$ = GREATER_OR_EQUAL_THAN; 
           printf("R-> >=\n");
         }
   | NEQ { 
           $$ = NOT_EQUALS;
           printf("R-> !=\n"); 
         }
   | EQ { 
          $$ = EQUALS; 
          printf("R-> ==\n");
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
        exit(1);
    }
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
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
            exit(1);
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
void verifica_call(char id[], int params[], int params_count) {
    // Buscando el renglón en la tabla de símbolos del identificador.
    int renglon = search(masterchef->st, id);
    if (renglon == -1) {
        // Erroe en caso de que no sea encontrada.
        yyerror("Error: La funcion que quieres llamar no ha sido declarado\n");
        exit(1);
    }
    // Checando que sea llamda con el mismo número de argumentos con que fue declarada.
    if (masterchef->st->symbols[renglon].num_args != params_count) {
        char error[1000];
        strcpy(error, "Error: El número de argumentos con la que fue llamada la función es incorrecto: ");
        yyerror2(error, id);
        exit(1);
    }
    // Checando que el tipo de los parámetros con que es llamda coincida con los de la declaración.
    for (int j = 0; j < params_count; j++) {
        if (masterchef->st->symbols[renglon].args[j] != params[j]) {
            char error[1000];
            strcpy(error, "Error: Los tipos de los argumentos que ingresaste no son correcto con la funcion: ");
            yyerror2(error, id);
            exit(1);
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
exp asignacion(char *id, char *id2, exp e, int trecibido){
    // La expresión que será devuelta.
    exp e1;
    e1.count_codigo = 0;
    // Cuando no es un var_arr:
    if(trecibido == -1) {
        int tipo;
        int es_estruct = 0;
        // Si no es de la forma id.id, el segundo id es vacío y podemos obtener el tipo del primero.
        if(strcmp(id2, "") == 0) {
            tipo = get_tipo_tablas(id);
        } else {
            // En otro caso, es de la forma id.id, entonces debemos buscar el primer identificador.
            es_estruct = 1;
            // Buscamos el id antes del punto en la tabla de símbolos para saber si fue declarado antes.
            int renglon = search(masterchef->st, id);
            if (renglon == -1) {
                yyerror("Error: El identificador no fue declarado\n");
                exit(1);
            }
            // Tenemos la tabla de tipos global.
            typetab tabla_tipos_actual= (*masterchef->tt);
            // Vemos si es de tipo struct la variable para poder hacer lo de id.id.
            int tiene_struct = tabla_tipos_actual.trs[masterchef->st->symbols[renglon].type].base.renglon;
            // Si sí tiene:
            if(tiene_struct == -2) {
                symtab *st_struct = tabla_tipos_actual.trs[stack_masterchefs->tabla->st->symbols[renglon].type].base.smt->st;
                // Buscando lo que hay después del punto en id.id.
                int renglon2 = search(st_struct, id2);
                if (renglon2 == -1) {
                    // Si no lo encontramos, tenemos que buscar en la global.
                    st_struct = tabla_tipos_actual.trs[masterchef->st->symbols[renglon].type].base.smt->st;
                    renglon2 = search(st_struct, id2);
                    // En este caso la estructura así antes.
                    if(renglon2 == -1) {
                        yyerror("Error: El struct no fue declarado como lo usaste.\n");
                        exit(1);
                    }
                }
                tipo = get_type(st_struct, id2);
                // En el caso contrario hay un error semántico.
            } else {
                yyerror2("Error: Intento de acceso a atributo de no estructura: ", id);
                exit(1);
            }
        }
        if( tipo != -1){        
            // El tipo de la expresión a devolver es el de la expresión luego de la asignación.
            e1.type = e.type;
            strcpy(e1.dir, id);
            // Creando la cuadrupla para la asignación y colocando la operación.
            cuadrupla c;
            c.op = ASSIGNATION;
            printf("%s %d %d\n", e.dir, tipo, e.type);
            // Colocando lo necesario de la cuadrupla.
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
            // Colocando lo respectivo al código a la expresión.
            e1.arr_codigo[e1.count_codigo] = c; 
            e1.count_codigo++;
        } else{
            // Caso para el error semántico.
            yyerror("Error: El identificador no fue declarado\n");
            exit(1);
        }
    } else {        // Aquí se maneja el caso para var_arr.
        e1.type = e.type;
        strcpy(e1.dir, id);
        // Crando la cuadrupla.
        cuadrupla c;
        c.op = ASSIGNATION;
        strcpy(c.op1, reducir(e.dir, trecibido, e.type));
        strcpy(c.op2, "");
        // En este caso id es la representacin de var_arr.
        strcpy(c.res, id);
        // Asociando lo respectivo al código a la expresión.
        e1.arr_codigo[e1.count_codigo] = c;
        e1.count_codigo++;}
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
        strcpy(e.dir, id);
    }else{
        // En otro caso buscamos el identificador en la tabla global.
        if(search(masterchef->st, id) !=-1){
            // Si ya lo encontramos, copiamos su valor en el dirección de la expresión.
            e.type = get_type(masterchef->st, id);
            strcpy(e.dir, id);
        } else {
            // Si no, entonces error porque no fue declarada antes.
            yyerror("Error: el identificador no existe");
            exit(1);
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
        c.op = EQ;
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
        c.op = EQ;
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
        c.op = EQ;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        return t;
    }            
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
        c.op = EQ;
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
        c.op = EQ;
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
        c.op = EQ;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un float\n");
        return t;
    }
    // En otro caso hay un error semántico.  
    printf("Error: Asignacion inconsistente de tipos.\n");
    exit(1);
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
    printf("%s\n", msg);
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
        printf("metemos ass\n");
        printf("%s, %s, %s, %d", c[j].op1, c[j].op2, c[j].res, c[j].op);
    }
}

int main(int argc, char **argv) {
    yyin = fopen(argv[1], "r");
    int result = yyparse();
    printf("resultado del analisis: %d\n", result);
    fclose(yyin);
    return 0;
}