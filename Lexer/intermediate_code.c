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
            case GOTO2:
                fprintf(CODIGO, "goto %s\n", temporal.res);
                printf("goto %s\n", temporal.res);
                break;
            case IFF2:
                fprintf(CODIGO, "if %s goto %s\n", temporal.op1, temporal.res);
                printf("if %s goto %s\n", temporal.op1, temporal.res);
                break;
            case LT2:
                fprintf(CODIGO, "%s = %s < %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s < %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case GT2:
                fprintf(CODIGO, "%s = %s > %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s > %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case LE2:
                fprintf(CODIGO, "%s = %s <= %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s <= %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case GE2:
                fprintf(CODIGO, "%s = %s >= %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s >= %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case EQ2:
                fprintf(CODIGO, "%s = %s == %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s == %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case NE2:
                fprintf(CODIGO, "%s = %s != %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s != %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case MA2:
                fprintf(CODIGO, "%s = %s + %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s + %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case MEN2:
                fprintf(CODIGO, "%s = %s - %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s - %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case ML2:
                fprintf(CODIGO, "%s = %s * %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s * %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case DV2:
                fprintf(CODIGO, "%s = %s / %s\n", temporal.res, temporal.op1, temporal.op2);
                printf("%s = %s / %s\n", temporal.res, temporal.op1, temporal.op2);
                break;
            case LB2:
                fprintf(CODIGO, "%s:", temporal.res);
                printf("%s:", temporal.res);
                break;
            case AS2:
                fprintf(CODIGO, "%s = %s\n", temporal.res, temporal.op1);
                printf("%s = %s\n", temporal.res, temporal.op1);
                break;
        }        
    }
    fclose(CODIGO);
}
