#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "mastertab.h"
#include "intermediate_code.h"

typedef struct _type{
	int type;
	int bytes;
} type;

typedef struct _args{
	int num;
	int lista_args[100];
} argumentos;

typedef struct _pii{
	char id1[32];
	char id2[32];
	int type;
} pii;

typedef struct _exp{
	cuadrupla arr_codigo[100];
	char dir[32];
	int type;
	int count_codigo;
} exp;

typedef struct _varr{
	char dir[32];
	typetab* tt;
	int type;
	char representacion[165];
} varr;

typedef struct _numero{
	int type;
	char val[33];
} numero;

typedef struct _caracter{
	int type;
	char val;
} caracter;

typedef struct _cadena{
	int type;
	char val[32];
} cadena;

typedef struct _arreglo{
	int tam;
	int dims[100];
} arreglo;


typedef struct _labels{
	cuadrupla arr_codigo[100];
	char label[100][32];
	int count;
	int count_codigo;
} labels;

char *pop_label(labels*);
void push_label(labels*, char *l);

char *get_top_label(labels*);    
char *get_top_label_previous(labels*);
void create_labels(labels*);
void print_stack_labels(labels*);
void print_list_labels(labels*);
    

#endif
