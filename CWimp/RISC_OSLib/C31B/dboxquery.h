/* dboxquery.h
 * Copyright (C) Acorn Computers Ltd., 1990
 * Copyright (C) Codemist Ltd., 1990
 */
#ifndef __dboxquery_h
#define __dboxquery_h
 
 
typedef enum
 {
 dboxquery_YES = 1, 
 dboxquery_NO = 2,
 dboxquery_CANCEL = 3
 } dboxquery_REPLY;
dboxquery_REPLY dboxquery(char *question);
#endif
