/* 
 * Archivo: pila.c
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 *          
 * Creado el 5 de diciembre de 2018.
 */

#include <stdio.h>
#include <stdlib.h>

#include "pila.h"
#include "mastertab.h"

/**
 * Función para meter una tabla maestra en la pila.
 * Una vez realizada la acción, devulve un apuntador
 * al nuevo tope de la pila (apuntador a nodo) trash el push.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
struct nodo* mete(struct nodo* pila, struct mastertab *tabla) {
    // Aloja memoria dinámicamente para el nodo.
    struct nodo* tmp = (struct nodo*)malloc(sizeof(struct nodo));
    // Establece sus apuntadores.
    tmp->tabla = tabla;
    tmp->siguiente = pila;
    pila = tmp;
    return pila;
}

/**
 * Función que extrae un elemento de la pila.
 * Debido a que necesitamos mantener vivos los apuntadores a 
 * los nodos porque necesitaremos sus apuntadores a las tablas, 
 * no los liberamos de la memoria con 'free'. Simplemente recorremos el 
 * apuntador del tope de la pila al que estaba debajo del tope previamente.
 *
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
struct nodo* saca(struct nodo *pila) {
	return pila->siguiente;
}

struct mastertab* tope(struct nodo *pila) {
    return pila->tabla;
}

/**
 * Función que imprime todo el contenido de la pila a partir
 * de un nodo.
 *
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
void imprime_pila(struct nodo* pila) {
    // Referencia al nodo actual.
    struct nodo *current;
    current = pila;
    // Vamos iterando sobre los nodos de la pila.
    if(current!= NULL) {
        printf("PILA: ");
        do {
            // En cada caso imprimimos las tablas de la
            // tabla maestra del nodo.
            print_type_table(current->tabla->tt);
            print_table(current->tabla->st);
            current = current->siguiente;
        } while (current!= NULL);
        printf("\n");
    }
    else {
        // Caso para manejar el escenario en que la pila sea vacía.
        printf("La pila está vacía.\n");
    }
 
}
