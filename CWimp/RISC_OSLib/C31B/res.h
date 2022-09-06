/* res.h
 * Copyright (C) Acorn Computers Ltd., 1990
 * Copyright (C) Codemist Ltd., 1990
 */
#ifndef __res_h
#define __res_h
#include <stdio.h> 
void res_init(const char *progname);
int res_findname(const char *resname, char *buf );
FILE *res_openfile(const char *resname, const char *mode);
#endif
