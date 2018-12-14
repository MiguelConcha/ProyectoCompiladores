/* 
 * Archivo: intermediate_code.h
 * Autores: Concha Vázquez Miguel
 *          Flores Martinez Andrés
 *          Gladín García Angel Iván
 *          Vázquez Salcedo Eduardo Eder
 *
 * Creado el 6 de diciembre de 2018.
 */

#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

/* Definiciones de las variables que identifican una operación dentro
 * del código intermedio */
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
#define PARAM 69
#define CALL 420
#define MAX_CODE 1000
    
/* Definición de la cuadrupla donde guardaremos una línea de código
 * del código intermedio. */
typedef struct _cuadrupla{
    /* Aquí es donde utilizamos las variables definidas arriba de este archivo. */
	int op;
	char op1[32];
	char op2[32];
	char res[65];
} cuadrupla;

/* Aquí es donde guardaremos todas nuyestras cuadruplas del coódigo intermedio */
typedef struct _intremediate_code{
	cuadrupla c[MAX_CODE];
	int count;
} ic;

/* Prototipos de las funciones declaradas en esta cabecera.
 * Para la descripción de estas funciones revizar intermediate_code.c */
void create_code(ic*);
int insert_cuad(ic*, cuadrupla);      
void print_code(ic*);

#endif 
