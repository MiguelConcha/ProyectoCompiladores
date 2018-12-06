#include "typetab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int insert_type_table(typetab* tt, typerow* tr){
    if(tt->count<1000){
        tt->trs[tt->count] = tr;
        tt->count++;        
        return 1;
    }
    return -1;
}

void print_type_table(typetab* tt) {
    int i;
    printf("POS\tTIPO\tTAMAÑO\tBASE\n");    
    for(i=0; i < tt->count; i++){
        printf("%d\t%d\t%d\t%d\n", i, tt->trs[i]->type, tt->trs[i]->tam, tt->trs[i]->base.renglon);        
    }
}

typerow* create_typerow(int tipo, int tamanio, int base, symtab *sm) {
    typerow *tr = (typerow *) malloc(sizeof(typerow));
    tr->type = tipo;
    tr->tam = tamanio;
    tr->base.renglon = base;
    tr->base.tss = sm;
    return tr;
}

void create_type_table(typetab *tt){
    tt->trs[0] = create_typerow(3, 1, -1, NULL);
    tt->trs[1] = create_typerow(0, 4, -1, NULL);
    tt->trs[2] = create_typerow(1, 4, -1, NULL);
    tt->trs[3] = create_typerow(2, 8, -1, NULL);
    tt->trs[4] = create_typerow(4, 1, -1, NULL);
    tt->count=5;
}
