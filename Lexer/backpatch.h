#ifndef BACKPATH_H
#define BACKPATH_H

#include "attributes.h"
#include "intermediate_code.h"
    
labels create_list(char*);

labels create_empty_list();
labels merge(labels*, labels*);
int backpatch(labels*, char*, ic*);
char *get_first(labels*);


#endif
