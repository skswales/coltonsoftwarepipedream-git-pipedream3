/* colourmenu.h
 * Copyright (C) Acorn Computers Ltd., 1990
 * Copyright (C) Codemist Ltd., 1990
 */
#ifndef __colourmenu_h
#define __colourmenu_h
#ifndef __menu_h
#include "menu.h"
#endif
#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif
menu colourmenu_make(char *title, BOOL includeNone);
#endif
