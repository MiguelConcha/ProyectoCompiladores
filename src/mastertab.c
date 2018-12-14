/* 
 * Archivo: mastertab.c
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 *          
 * Creado el 4 de diciembre de 2018.
 */

#include "mastertab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Función que sirve para buscar el índice del renglón correspondiente
 * de la tabla de símbolos dada como argumento en que se ubica
 * el identificador pasado como segundo argumento.
 * Devuelve un -1 en caso de no encontrarlo en la tabla.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
int search(symtab *st, char*id){
    int i;
    // Iterando sobre la tabla hasta su máximo número de renglones buscando
    // el identificador.
    for(i=0; i <st->count; i++){
        if(strcmp(st->symbols[i].id, id)==0)
            return i;
    }
    return -1;
}

/**
 * Función que sirve insertar un nuevo renglón en la tabla de símbolos
 * dada como argumento.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
int insert(symtab *st, sym s){
    // Primero busca que no se encuentre el identificador del renglón que se quiere
    // meter y que no se haya rebasado el máximo número de renglones posibles en la tabla.
    if(search(st, s.id)==-1 && st->count<1000){
        st->symbols[st->count] = s;
        st->count++;        
        return 1;
    }
    // En caso de violar alguna condición regresa -1.
    return -1;
}

/**
 * Imprime la tabla de símbolos dada como argumento.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
void print_table(symtab* st){    
    int i;
    // Encabezado para la impresión.
    printf("POS\tID\tTIPO\tDIR\tVAR\tARGS\n");    
    for(i=0; i < st->count; i++){
		char rep[st->symbols[i].num_args+1000];
		strcpy(rep, "");
        // Obteniendo la representación de los argumentos.
        // Si no se cuenta, imprime una línea en blanco.
        // En el otro caso tienen que ir concatentando los tipos a una cadena.
		if(st->symbols[i].var != 1 || st->symbols[i].num_args == 0) {
			strcpy(rep, "---");
		} else {
			for(int j = 0; j < st->symbols[i].num_args;j++){
				char tmp[100];
				sprintf(tmp, "(%s,%d)", map_type(st->symbols[i].args[j][0]), st->symbols[i].args[j][1]);
				strcat(rep, tmp);
				strcat(rep, " ");
			}
		}
        // Imprimiendo el renglón de la iteración actual.
        printf("%d\t%s\t%d\t%d\t%d\t%s\n", i, st->symbols[i].id, st->symbols[i].type, st->symbols[i].dir, st->symbols[i].var, rep);       
    }
}

/**
 * Devuelve la dirección en donde empieza el identificador
 * dado como segundo argumento.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
int get_dir(symtab *st, char* id){
    int i;
    for(i=0; i< st->count; i++){
        if(strcmp(st->symbols[i].id,id)==0)
            // Regresando la dirección del renglón.
            return st->symbols[i].dir;
    }
    return -1;
}

/**
 * Devuelve el tipo en donde empieza el identificador
 * dado como segundo argumento.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
int get_type(symtab* st, char *id){
    int i;
    for(i=0; i< st->count; i++){
        if(strcmp(st->symbols[i].id,id)==0) {
            // Regresando el tipo del renglón.
            return st->symbols[i].type;
			printf("lo encontre\n");
		}
    }
    return -1;
}

/**
 * Crea una tabla de tipos. Lo único que hace es inicializar
 * su contador de renglones en cero, pues la asignación de memoria
 * dinámica se hará para la tabla maestra que contenga este apuntador.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
void create_table(symtab *st){
    st->count=0;
}

/**
 * Función que sirve insertar un nuevo renglón en la tabla de tipos
 * dada como argumento.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
int insert_type_table(typetab* tt, typerow tr){
    // Aquí verificamos que todavía pueda ser añadida a la tabla.
    if(tt->count<1000){
        tt->trs[tt->count] = tr;
        tt->count++;        
        return 1;
    }
    return -1;
}

/**
 * Función que sirve para transformar ('mapear') un entero
 * a su tipo como cadena para poder llevar a cabo la impresión 
 * adecuada de las tablas de tipos y símbolos en consola.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
char* map_type(int t) {
    // Se hace una verificación por casos para saber qué devolver.
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
    if (t== 7)
        return "FUNC";
    char *str = (char*)malloc(100);
    sprintf(str, "%d", t);
    return str;
}

/**
 * Imprime la tabla de tipos dada como argumento.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
void print_type_table(typetab* tt) {
    int i;
    // Encabezado de la tabla que será impresa en consola.
    printf("POS\tTIPO\tTAMAÑO\tBASE\n");    
    for(i=0; i < tt->count; i++){
        // Imprimiendo el renglón actual de la iteración.
        printf("%d\t%s\t%d\t%d\n", i, map_type(tt->trs[i].type), tt->trs[i].tam, tt->trs[i].base.renglon);        
    }
}

/**
 * Crea una tabla de tipos. En este caso inicializamos simpre las tablas
 * de tipos con los cinco renglones correspondientes a los tipos básicos.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedor Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
void create_type_table(typetab *tt){

    // Alojando memoria dinámica para los renglones que serán añadidos siempre a la tabla.
    typerow *row1 = (typerow *) malloc(sizeof(typerow));
    typerow *row2 = (typerow *) malloc(sizeof(typerow));
    typerow *row3 = (typerow *) malloc(sizeof(typerow));
    typerow *row4 = (typerow *) malloc(sizeof(typerow));
    typerow *row5 = (typerow *) malloc(sizeof(typerow));
    
    // Estabeciendo los tipos y tamaños de los tipos básicos (char, int, float, double y void).
    // Ellos no tienen un apuntador a una tabla maestra.
    row1->type = 3; row1->tam=1; row1->base.renglon=-1; row1->base.smt=NULL;
    row2->type = 0; row2->tam=4; row2->base.renglon=-1; row2->base.smt=NULL;
    row3->type = 1; row3->tam=4; row3->base.renglon=-1; row3->base.smt=NULL;
    row4->type = 2; row4->tam=8; row4->base.renglon=-1; row4->base.smt=NULL;
    row5->type = 4; row5->tam=1; row5->base.renglon=-1; row5->base.smt=NULL;

    // Agregando los cinco renglones a la tabla de tipos pasada como argumento.
    tt->trs[0] = *row2;
    tt->trs[1] = *row3;
    tt->trs[2] = *row4;
    tt->trs[3] = *row1;
    tt->trs[4] = *row5;
    
    // Establecemos el contador en cinco por los cinco renglones que agregamos.
    tt->count=5;
}

