/* 
 * Archivo: intermediate_code.c
 * Authors: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 			
 * Creado el 6 de diciembre de 2018.
 */

#include "intermediate_code.h"
#include <stdio.h>

/**
 * Asignamos el count de la tabla de cuadruplas a cero para que se
 * empiecen a insertar las cuadruplas desde esta posición.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
void create_code(ic* code){
    code->count= 0;
}

/**
 * Insertamos una cuadrupla a la tabla de cuadruplas que ha sido enviada.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
int insert_cuad(ic* code, cuadrupla c){
    if(code->count<MAX_CODE){
        code->c[code->count++] = c;
        return code->count-1;
    }
    return -1;
}


/**
 * Imprimimos la tabla de cuadruplas.
 * Para imprimirlo de manera más entendible hacemos un mapeo de las operaciones
 * con su representación en cadena y mostrar de manera correcta dependiendo de
 * la operación.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
void print_code(ic* code){
    FILE * CODIGO;
    CODIGO = fopen("codigo.ci", "w");
    int i;
    for(i=0; i < code->count; i++){
        cuadrupla temporal = code->c[i];
        switch(temporal.op){
            case GOTO:
                fprintf(CODIGO, "goto %s\n", temporal.res);
                printf("goto %s\n", temporal.res);
                break;
            case IFF:
                fprintf(CODIGO, "if %s goto %s\n", temporal.op1, temporal.res);
                printf("if %s goto %s\n", temporal.op1, temporal.res);
                break;
            case LESS_THAN:
                fprintf(CODIGO, "%s = %s < %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s < %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case GREATER_THAN:
                fprintf(CODIGO, "%s = %s > %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s > %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case LESS_OR_EQUAL_THAN:
                fprintf(CODIGO, "%s = %s <= %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s <= %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case GREATER_OR_EQUAL_THAN:
                fprintf(CODIGO, "%s = %s >= %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s >= %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case EQUALS:
                fprintf(CODIGO, "%s = %s == %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s == %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case NOT_EQUALS:
                fprintf(CODIGO, "%s = %s != %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s != %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case MAS:
                fprintf(CODIGO, "%s = %s + %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s + %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case MENOS:
                fprintf(CODIGO, "%s = %s - %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s - %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case MULTIPLICACION:
                fprintf(CODIGO, "%s = %s * %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s * %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case DIVISION:
                fprintf(CODIGO, "%s = %s / %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s / %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case MODULO:
                fprintf(CODIGO, "%s = %s / %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s / %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case LABEL:
                fprintf(CODIGO, "%s:", temporal.res);
                printf("%s:", temporal.res);
                break;
            case ASSIGNATION:
                fprintf(CODIGO, "%s = %s\n", temporal.res, temporal.op1);
                printf("%s = %s\n", temporal.res, temporal.op1);
                break;
            case PARAM:
                fprintf(CODIGO, "param %s\n", temporal.res);
                printf("param %s\n", temporal.res);
                break;
            case CALL:
                fprintf(CODIGO, "%s = call %s, %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = call %s, %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
        }        
    }
    fclose(CODIGO);
}
