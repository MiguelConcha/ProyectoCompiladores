#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#define GOTO2 1
#define IFF2 2
#define LT2 3
#define GT2 4
#define LE2 5
#define GE2 6
#define EQ2 7
#define NE2 8
#define MA2 9
#define MEN2 10
#define ML2 11
#define DV2 12
#define LB2 13
#define AS2 14
#define MAX_CODE 1000
    
typedef struct _cuadrupla{
	int op;
	char op1[32];
	char op2[32];
	char res[32];
}cuadrupla;

	
typedef struct _intremediate_code{
	cuadrupla c[MAX_CODE];
	int count;
}ic;

void create_code(ic*);
int insert_cuad(ic*, cuadrupla);      
void print_code(ic*);




#endif 
