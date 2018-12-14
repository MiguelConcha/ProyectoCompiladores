/* 
 * Archivo: pila.h
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 *          
 * Creado el 5 de diciembre de 2018.
 */

#pragma once
#ifndef _PILA_
#define _PILA_

#include <stdio.h>
#include "mastertab.h"
int yylex();

/* Estructura para los nodos de la pila: tienen un apuntador a un siguiente nodo 
   y cada nodo guarda un apuntador a una tabla maestra (que tiene un apuntador a
   una tabla de símbolos y a una de tipos). */
struct nodo {
    struct mastertab *tabla;
    struct nodo* siguiente;
};


/* Prototipos para las funciones que se tendrán para operar con la pila. 
   Para ahondar en su funcionamiento, consultar el archivo pila.c. */
struct nodo* mete(struct nodo*, struct mastertab*);
struct nodo* saca(struct nodo*);
struct mastertab* tope(struct nodo*);
void imprime_pila(struct nodo*);
int vacia(struct nodo*);

#endif