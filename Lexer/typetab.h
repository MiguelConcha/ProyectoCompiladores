#ifndef TYPETAB_H
#define TYPETAB_H

#include "symtab.h"

struct _typerow{
	int type;
	int tam;
	struct{
		int renglon;
		symtab *tss;
	}base;
};

typedef struct _typerow typerow;

typedef struct _ttab{
		typerow trs[100];
		int count;
} typetab;

int insert_type_table(typetab* , typerow);
void print_type_table(typetab*);
typerow create_typerow(int, int, int, symtab*);
void create_type_table(typetab*);
    
#endif
