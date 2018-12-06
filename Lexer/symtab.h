#ifndef SYMTAB_H
#define SYMTAB_H


struct _symbol{
	char id[32];
	int type;
	int dir;
	int var;
	int args[100];
};

typedef struct _symbol sym;

typedef struct _symtab{
	sym symbols[1000];
	int count;
} symtab;

int search(symtab *, char*);
int insert(symtab*, sym );
void print_table(symtab*);
int get_dir(symtab*, char*);
int get_type(symtab*, char *);
void create_table(symtab *st);
    


#endif
