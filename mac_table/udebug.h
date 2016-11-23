#ifndef _MAC_DEBUG_H_
#define _MAC_DEBUG_H_
/*******************************************************************************
 * include segement
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include "mactable.h"

#ifdef DEBUG

#define NEXT_FIELD(i) (i+1 >= TABLE_LENGTH ? i+1:0)


/*******************************************************************************
 * debug function
*******************************************************************************/
void sizeofstruct(void);
void debug_find(void);
void debug_charat(struct mac_field);
#endif

#endif /* _MAC_TABLE_H_ */
