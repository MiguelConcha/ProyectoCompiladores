/* 
 * Archivo: attributes.h
 * Autores: Concha Vázquez Miguel
 *          Flores Martinez Andrés
 *          Gladín García Angel Iván
 *          Vázquez Salcedo Eduardo Eder
 *
 * Creado el 5 de diciembre de 2018.
 */

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

/* Tabla de tipos y símbolos */
#include "mastertab.h"
/* Tipos del código intermedio */
#include "intermediate_code.h"

/* Para los tokens de tipos */
typedef struct _type{
	int type;
	int bytes;
} type;

/* Para los argumentos de las funciones */
typedef struct _args{
	int num;
	int lista_args[100];
} argumentos;

/* Para la parte izquierda que se utiliza en la asignacion */
typedef struct _pii{
	char id1[32];
	/* Para queremos obtener el atributo dentro de un struct */
	char id2[32];
	int type;
} pii;

/* Para las expresiones */
typedef struct _exp{
    /* Codigo que se guarda en la expresión */
	cuadrupla arr_codigo[100];
	/* Dirección donde se guarda el resultado de la evaluación de la expresión */
	char dir[32];
	int type;
	/* Número de cuadruplas que guardamos */
	int count_codigo;
} exp;

/* Para el var arreglo */
typedef struct _varr{
	char dir[32];
	typetab* tt;
	int type;
	/* Donde guardamos la representación en string del var arr */
	char representacion[165];
} varr;

/* Para los tokens de números */
typedef struct _numero{
	int type;
	/* Para evitar guarda un posible de cada tipo, guardamos el valor en un arreglo
	 * de caracteres */
	char val[33];
} numero;

/* Para el token de caracter */
typedef struct _caracter{
	int type;
	char val;
} caracter;

/* Para el token de cadena */
typedef struct _cadena{
	int type;
	char val[32];
} cadena;

/* Para guardar el tamaño del arreglo (que son las dimensiones del arreglo) y
 * los enteros que nos indican el tamaño de cada dimensión */
typedef struct _arreglo{
	int tam;
	int dims[100];
} arreglo;

/* Para hacer el backpatch */
typedef struct _labels{
	cuadrupla arr_codigo[100];
	char label[100][32];
	int count;
	int count_codigo;
} labels;

/* Prototipos de las funciones declaradas en esta cabecera.
 * Para la descripción de estas funciones revizar attributes.c */
char *pop_label(labels*);
void push_label(labels*, char *l);

char *get_top_label(labels*);    
char *get_top_label_previous(labels*);
void create_labels(labels*);
void print_stack_labels(labels*);
void print_list_labels(labels*);
    

#endif
