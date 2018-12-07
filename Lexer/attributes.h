#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H
    
typedef struct _type{
	int type;
	int bytes;
} type;

typedef struct _exp{
	char dir[32];
	int type;
} exp;

typedef struct _numero{
	int type;
	char val[32];
} numero;

typedef struct _caracter{
	int type;
	char val;
} caracter;

typedef struct _cadena{
	char val[100];
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
