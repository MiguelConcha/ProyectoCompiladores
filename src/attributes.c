/* 
 * Archivo: attributes.c
 * Authors: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 			
 * Creado el 5 de diciembre de 2018.
 */

#include "attributes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 

/**
 * Quita la etiqueta que está en el tope de la pila de etiquetas enviada.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
char *pop_label(labels* ls){
    char *t= (char*) malloc(32*sizeof(char));
    if(ls->count>-1){        
        strcpy(t,ls->label[ls->count-1]);
        ls->count--;        
    }
    return t;
}

/**
 * Agrega una etiqueta en el tope de la pila de etiquetas enviada.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
void push_label(labels* ls, char *l){
    if(ls->count<100){
        strcpy(ls->label[ls->count], l);
        ls->count++;
    }
}

/**
 * Regresa la etiqueta que está en el tope de la pila de etiquetas enviada.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
char *get_top_label(labels* ls){
    return ls->label[ls->count-1];
}

/**
 * Regresa la etiqueta que está debajo del tope de la pila de etiquetas enviada.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
char *get_top_label_previous(labels* ls){
    return ls->label[ls->count-2];
}

/**
 * Asigna el count de la pila de etiquetas a cero.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
void create_labels(labels* ls){
    ls->count=0;
}

/**
 * Imprime las etiquetas en forma de pila.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
void print_stack_labels(labels* ls){
    int i;
    printf("LABELS\n");
    for(i=ls->count-1; i >-1; i--){
        printf("%s\n", ls->label[i]);
    }
}

/**
 * Imprime las etiquetas en forma de lista.
 * 
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
void print_list_labels(labels* ls){
    int i;
    printf("LABELS\n");
    for(i=0;i<ls->count; i++){
        printf("%s\n", ls->label[i]);
    }
}
