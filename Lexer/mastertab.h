#ifndef MASTERTAB_H
#define MASTERTAB_H

struct mastertab;

struct _symbol{
	char id[32];
	int type;
	int dir;
	int var;
	int args[100];
};

typedef struct _symbol sym;

typedef struct _symtab{
	sym symbols[100];
	int count;
} symtab;

int search(symtab *, char*);
int insert(symtab*, sym);
void print_table(symtab*);
int get_dir(symtab*, char*);
int get_type(symtab*, char *);
void create_table(symtab *st);

struct _typerow{
	int type;
	int tam;
	struct{
		int renglon;
		struct mastertab *smt;
	}base;
};

typedef struct _typerow typerow;

typedef struct _ttab{
		typerow trs[100];
		int count;
} typetab;

struct mastertab {
	typetab *tt;
	symtab *st;
};

int insert_type_table(typetab* , typerow);
void print_type_table(typetab*);
typerow create_typerow(int, int, int, symtab*);
void create_type_table(typetab*);

#endif
