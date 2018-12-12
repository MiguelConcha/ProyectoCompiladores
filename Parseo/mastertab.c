#include "mastertab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search(symtab *st, char*id){
    int i;
    for(i=0; i <st->count; i++){
        if(strcmp(st->symbols[i].id, id)==0)
            return i;
    }
    return -1;
}

int insert(symtab *st, sym s){
    if(search(st, s.id)==-1 && st->count<1000){
        st->symbols[st->count] = s;
        st->count++;        
        return 1;
    }
    return -1;
}

void print_table(symtab* st){    
    int i;
    printf("POS\tID\tTIPO\tDIR\n");    
    for(i=0; i < st->count; i++){
        printf("%d\t%s\t%d\t%d\n", i, st->symbols[i].id, st->symbols[i].type, st->symbols[i].dir);        
    }
}

int get_dir(symtab *st, char* id){
    int i;
    for(i=0; i< st->count; i++){
        if(strcmp(st->symbols[i].id,id)==0)
            return st->symbols[i].dir;
    }
}

int get_type(symtab* st, char *id){
    int i;
    for(i=0; i< st->count; i++){
        if(strcmp(st->symbols[i].id,id)==0)
            return st->symbols[i].type;
    }
}

void create_table(symtab *st){
	//st = (symtab *) malloc(sizeof(symtab));
    st->count=0;
}

int insert_type_table(typetab* tt, typerow tr){
    if(tt->count<1000){
        tt->trs[tt->count] = tr;
        tt->count++;        
        return 1;
    }
    return -1;
}

char* map_type(int t) {
    if (t== 0)
        return "INT";
    if (t== 1)
        return "FLOAT";
    if (t== 2)
        return "DOUB";
    if (t== 3)
        return "CHAR";
    if (t== 4)
        return "VOID";
    if (t== 5)
        return "ARR";
	if (t == 6)
		return "STRUCT";
    char *str = (char*)malloc(100);
    sprintf(str, "%d", t);
    return str;
}

void print_type_table(typetab* tt) {
    int i;
    printf("POS\tTIPO\tTAMAÑO\tBASE\n");    
    for(i=0; i < tt->count; i++){
        printf("%d\t%s\t%d\t%d\n", i, map_type(tt->trs[i].type), tt->trs[i].tam, tt->trs[i].base.renglon);        
    }
}

void create_type_table(typetab *tt){
	//tt = (typetab *) malloc(sizeof(typetab));
    typerow *row1 = (typerow *) malloc(sizeof(typerow));
    typerow *row2 = (typerow *) malloc(sizeof(typerow));
    typerow *row3 = (typerow *) malloc(sizeof(typerow));
    typerow *row4 = (typerow *) malloc(sizeof(typerow));
    typerow *row5 = (typerow *) malloc(sizeof(typerow));
    
    row1->type = 3; row1->tam=1; row1->base.renglon=-1; row1->base.smt=NULL;
    row2->type = 0; row2->tam=4; row2->base.renglon=-1; row2->base.smt=NULL;
    row3->type = 1; row3->tam=4; row3->base.renglon=-1; row3->base.smt=NULL;
    row4->type = 2; row4->tam=8; row4->base.renglon=-1; row4->base.smt=NULL;
    row5->type = 4; row5->tam=1; row5->base.renglon=-1; row5->base.smt=NULL;

    //printf("%d\t%s\t%d\t%d\n", 0, map_type(row1->type), row1->tam, row1->base.renglon);        

    tt->trs[0] = *row2;
    tt->trs[1] = *row3;
    tt->trs[2] = *row4;
    tt->trs[3] = *row1;
    tt->trs[4] = *row5;
    
    tt->count=5;
}

