/*******************************************************************************
 * include segement
*******************************************************************************/
#include <stdio.h>
#include "mactable.h"
#include "udebug.h"

/*******************************************************************************
 * debug function
*******************************************************************************/
int loop()
{
	while (1) {
		return 0;
	}
	return 1;
}

int main()
{
	mactable_init();
#ifdef DEBUG
	// sizeofstruct();
	debug_find();
#endif

	int flag = loop();
	mactable_exit();
	return flag;
}
