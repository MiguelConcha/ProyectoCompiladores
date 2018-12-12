#include <stdio.h>
#include <stdlib.h>

#include "pila.h"
#include "mastertab.h"

/*
 * Mete un elemento en el stack.
 * Autores: Miguel Concha, Andrés Flores, Pedro Sánchez.
 * Fecha de programación: 12-11-18
 */
struct nodo* mete(struct nodo* pila, struct mastertab *tabla) {
    struct nodo* tmp = (struct nodo*)malloc(sizeof(struct nodo));
    tmp->tabla = tabla;
    tmp->siguiente = pila;
    pila = tmp;
    return pila;
}
/*
 * Saca un elemento de la pila y lo almacena en la dirección a la que apunta el apuntador 
 * elemento.
 * Autores: Miguel Concha, Andrés Flores, Pedro Sánchez.
 * Fecha de programación: 12-11-18
*/
struct nodo* saca(struct nodo *pila, struct mastertab *tabla) {
    struct nodo* tmp = pila;
    tabla = pila->tabla;
    pila = pila->siguiente;
    free(tmp);
    return pila;
}

/*
 * Imprime el contenido de la pila en consola y el archivo que recibe como parámetro.
 * Autores: Miguel Concha, Andrés Flores, Pedro Sánchez.
 * Fecha de programación: 12-11-18
 */
void imprime_pila(struct nodo* pila) {
    struct nodo *current;
    current = pila;
    if(current!= NULL) {
        printf("PILA: ");
        do {
            print_type_table(current->tabla->tt);
            print_table(current->tabla->st);
            current = current->siguiente;
        } while (current!= NULL);
        printf("\n");
    }
    else {
        printf("La pila está vacía.\n");
    }
 
}
