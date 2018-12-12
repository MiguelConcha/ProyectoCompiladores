#pragma once
#ifndef _PILA_
#define _PILA_

#include <stdio.h>
#include "mastertab.h"

int yylex();

struct nodo {
    struct mastertab *tabla;
    struct nodo* siguiente;
};

struct nodo* mete(struct nodo*, struct mastertab*);
struct nodo* saca(struct nodo*);
struct mastertab* tope(struct nodo*);
void imprime_pila(struct nodo*);
int vacia(struct nodo*);

#endif
