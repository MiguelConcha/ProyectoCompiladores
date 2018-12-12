#include "intermediate_code.h"
#include <stdio.h>

void create_code(ic* code){
    code->count= 0;
}


int insert_cuad(ic* code, cuadrupla c){
    if(code->count<MAX_CODE){
        code->c[code->count++] = c;
        return code->count-1;
    }
    return -1;
}


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
        }        
    }
    fclose(CODIGO);
}
