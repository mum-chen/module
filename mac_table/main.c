/*******************************************************************************
 * include segement
*******************************************************************************/
#include <stdio.h>

#include "mactable.h"

/*******************************************************************************
 * debug function
*******************************************************************************/
void debug_charat(struct mac_field f)
{
	unsigned char a = CHAR_AT_MAC(f.mac, 1);
	printf("print mac %lx(0:%x)\n", f.mac, a);
}


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
	struct mac_field f = {
		.mac = 0xa1b1c1,
		.tag = 3,
		.resv = 1,
		.next = 11,
	};

	setport(f.mac, f.tag);

	unsigned char port = getport(f.mac);
	
	printf("port:%d\n", port);
	int flag = loop();
	mactable_exit();
	return flag;
}
