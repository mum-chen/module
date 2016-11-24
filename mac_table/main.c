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
	uint64_t mac_64 = 0;
	uint8_t mac[6] = { 0xff,  0x11, 0x22, 0x33, 0x44, 0x55,};

	mactable_init();

#ifdef DEBUG
	// mac_64 = transmac(mac);
	// PDEBUG("\n");
	sizeofstruct();
	debug_find();
#endif

	int flag = loop();
	mactable_exit();
	return flag;
}
