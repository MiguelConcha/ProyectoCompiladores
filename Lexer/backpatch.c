/* 
 * Archivo: backpatch.c
 * Authors: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 			
 * Creado el 10 de diciembre de 2018.
 */

#include "backpatch.h"
#include "intermediate_code.h"
#include <stdio.h>
#include <string.h>

/**
 * Crea una lista de etiquetas y agrega al tope la etiqueta que ha sido enviada.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 10 de diciembre de 2018.
 */
labels create_list(char* l){
    labels ls;
    create_labels(&ls);
    strcpy(ls.label[ls.count], l);
    ls.count++;
    return ls;
}

/**
 * Crea una lista de etiquetas vacía.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 10 de diciembre de 2018.
 */
labels create_empty_list(){
    labels ls;
    create_labels(&ls);    
    return ls;
}

/**
 * Mezcla 2 listas de etiquetas.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 10 de diciembre de 2018.
 */
labels merge(labels* ls1, labels* ls2){
    labels ls;
    create_labels(&ls);
    int i;
    for(i =0; i< ls1->count;i++){
        strcpy(ls.label[ls.count++], ls1->label[i]);
    }
    for(i =0; i< ls2->count;i++){
        strcpy(ls.label[ls.count++], ls2->label[i]);
    }
    return ls;
}

/**
 * Hace el Backpatch.
 * Para más información revisar el libro del Dragón.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 10 de diciembre de 2018.
 */
int backpatch(labels* ls, char* l, ic* code){
    int i, j;
    for(i=0; i < ls->count; i++){
        for(j=0; j<code->count; j++){
            if(strcmp(code->c[j].res, ls->label[i])==0){
                strcpy(code->c[j].res, l);
            }
        }
    }
}

/**
 * Regresa la etiqueta que está en al inicio de la lista.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 10 de diciembre de 2018.
 */
char *get_first(labels* ls){
    return ls->label[0];
}
