/* 
 * Archivo: mastertab.h
 * Autores: Concha Vázquez Miguel
 * 			Flores Martínez Andrés
 * 			Gladín García Ángel Iván
 *  		Sánchez Pérez Pedro Juan Salvador
 *			Vázquez Salcedor Eduardo Eder
 * 			
 * Creado el 4 de diciembre de 2018.
 */

#ifndef MASTERTAB_H
#define MASTERTAB_H

// Estructura que tiene apuntadores a una tabla de símbolos y a una tabla de tipos.
struct mastertab;

// Estructura para un renglón de las tablas de símbolos.
struct _symbol{
	char id[32];
	int type;
	int dir;
	int var;
	int args[100];
	int num_args;
};

// Creando un alias para la estructura previa.
typedef struct _symbol sym;

/* Estructura la tabla de símbolos. Tenemos un campo contador para poder
   saber en donde tendremos que insertar nuevos renglones en la tabla. 
   Aquí mismo hacemos un alias. */
typedef struct _symtab{
	sym symbols[100];
	int count;
} symtab;

/* Prototipos para las funciones que se tendrán para manipular y hacer
   consultas a las tablas de símbolos. Para ahondar en su funcionamiento,
   consultar el archivo mastertab.c. */
int search(symtab *, char*);
int insert(symtab*, sym);
void print_table(symtab*);
int get_dir(symtab*, char*);
int get_type(symtab*, char *);
void create_table(symtab *st);
char* map_type(int);

// Estructura para un renglón de las tablas de tipos.
struct _typerow{
	int type;
	int tam;
	/* Con el entero "renglon" indicaremos si en efecto cuenta o no con el 
	   apuntador a una tabla mastra. Aplicará en los casos para las funciones
	   y estructuras. */
	struct{
		int renglon;
		struct mastertab *smt;
	}base;
};

// Alias para los renglones de las tablas de tipos.
typedef struct _typerow typerow;

/* Estructura la tabla de tipos. Tenemos un campo contador para poder
   saber en donde tendremos que insertar nuevos renglones en la tabla. 
   Aquí mismo hacemos un alias. */
typedef struct _ttab{
		typerow trs[100];
		int count;
} typetab;

/* Estructura para las tablas maestras que tienen los apuntadores a las tablas
   tipos y de símbolos. Sirve para poder "ligarlas" a ambas. */
struct mastertab {
	typetab *tt;
	symtab *st;
};

/* Prototipos para las funciones que se tendrán para manipular y hacer
   consultas a las tablas de tipos. Para ahondar en su funcionamiento,
   consultar el archivo mastertab.c. */
int insert_type_table(typetab* , typerow);
void print_type_table(typetab*);
typerow create_typerow(int, int, int, symtab*);
void create_type_table(typetab*);

#endif