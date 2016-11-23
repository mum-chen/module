/*******************************************************************************
 * include segement
*******************************************************************************/
#include "mactable.h"
#include "udebug.h"

/*******************************************************************************
 * debug function
*******************************************************************************/
#ifdef DEBUG
/*******************************************************************************
 * global variable declare
*******************************************************************************/
extern struct mac_ctr	*controller;
extern struct mac_field	*mactable;

/*******************************************************************************
 * debug function
*******************************************************************************/
void sizeofstruct(void)
{
	printf("Hello, world contro:%ld, mac_field:%ld \n",
		sizeof(struct mac_ctr), sizeof(struct mac_field));
	
	printf("Hello, world p-contro:%ld, p-mac_field:%ld \n",
		sizeof(controller), sizeof(mactable));

	int a = VALID_TABLE_LENGTH;

	printf("vaild table number is %d\n", a);
}

void debug_charat(struct mac_field f)
{
	unsigned char a = CHAR_AT_MAC(f.mac, 1);
	printf("print mac %lx(0:%x)\n", f.mac, a);
}

void debug_find(void)
{
	/* find empty */
#if 0
	printf("empty, port:%u\n", getport(0xa1b1c3));

#endif

	/* find exist */
#if 0
	setport(0xa1b1c2, 2);
	setport(0x11111111, 1);
	setport(0xa1b1c2, 1);
	setport(0xa1b1c3, 1);

	printf("exist, port:%u\n", getport(0xa1b1c2));
	printf("exist, port:%u\n", getport(0x11111111));
#endif
	/* find conflict */
#if 0
	/* conflict 0xa1b1c1, 0x111111 */
	setport(0xa1b1c1, 2);
	setport(0x111111, 3);

	printf("conflict, port:%u\n", getport(0xa1b1c1));
	printf("conflict, port:%d\n", getport(0x111111));
#endif
	/* find all loop */
#if 0
	uint16_t i = 0;
	printf("setting\n");
	for(i = 0; i < TABLE_LENGTH; i++){
		mactable[i].used = FIELD_DELETED;
	}
	printf("prepare fin\n");
	setport(0xa1b1c1, 1);
	printf("full, port:%u\n", getport(0xa1b1c1));
	// Check did find function into a dead loop?
	// and check the times during finding.
#endif

	/* check autoremove */
#if 1

#define PORT(i)	((i & 0x1) ? 1 : 2)
	uint16_t i = 0, n;
	for (i = 0; i < 2000 ;i ++){
		setport(i, PORT(i));
	}

	for (i = 0; i < 2000 ;i ++){
		if (getport(i) != PORT(i))
			n++;
	}
	printf("n:%u\n", n);
#endif
}

#endif
