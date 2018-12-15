/* 
 * Archivo: backpatch.h
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 *          
 * Creado el 10 de diciembre de 2018.
 */

#ifndef BACKPATCH_H
#define BACKPATCH_H

#include "attributes.h"
#include "intermediate_code.h"
    
/* Prototipos para las funciones necesarias para el backpatch.
   Para ahondar en su funcionamiento, consultar el archivo backpatch.c. */
labels create_list(char*);
labels create_empty_list();
labels merge(labels*, labels*);
int backpatch(labels*, char*, ic*);
char *get_first(labels*);

#endif