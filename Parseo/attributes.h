#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "mastertab.h"

typedef struct _type{
	int type;
	int bytes;
} type;


typedef struct _pii{
	char id1[32];
	char id2[32];
	int type;
} pii;

typedef struct _exp{
	char dir[32];
	int type;
} exp;

typedef struct _varr{
	char dir[32];
	typetab* tt;
	int type;
	char representacion[165];
} varr;

typedef struct _numero{
	int type;
	char val[32];
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
	char label[100][32];
	int count;
} labels;

char *pop_label(labels*);
void push_label(labels*, char *l);

char *get_top_label(labels*);    
char *get_top_label_previous(labels*);
void create_labels(labels*);
void print_stack_labels(labels*);
void print_list_labels(labels*);
    

#endif
