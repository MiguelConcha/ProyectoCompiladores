#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mastertab.h"
#include "attributes.h"
#include "backpatch.h"
#include "intermediate_code.h"

extern FILE* yyin;
extern int yyparse();

int main(int argc, char **argv) {
    yyin = fopen(argv[1], "r");
    int result = yyparse();
    if(result) {
    	printf("El programa tiene errores sintacticos\n");
    } else 
    	printf("COMPILADO\n");
    fclose(yyin);
    return 0;
}
