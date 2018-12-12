#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#define GOTO 1
#define IFF 2
#define LESS_THAN 3
#define GREATER_THAN 4
#define LESS_OR_EQUAL_THAN 5
#define GREATER_OR_EQUAL_THAN 6
#define EQUALS 7
#define NOT_EQUALS 8
#define MAS 9
#define MENOS 10
#define MULTIPLICACION 11
#define DIVISION 12
#define MODULO 13
#define LABEL 14
#define ASSIGNATION 15
#define MAX_CODE 1000
    
typedef struct _cuadrupla{
	int op;
	char op1[32];
	char op2[32];
	char res[65];
}cuadrupla;

	
typedef struct _intremediate_code{
	cuadrupla c[MAX_CODE];
	int count;
}ic;

void create_code(ic*);
int insert_cuad(ic*, cuadrupla);      
void print_code(ic*);

#endif 
