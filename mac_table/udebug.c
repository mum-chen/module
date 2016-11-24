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
	printf("print mac %x(0:%x)\n", f.mac, a);
}

void debug_find(void)
{
	/* find empty */
#if 0
	uint8_t mac[6] = { 0xff,  0x11, 0x22, 0x33, 0x44, 0x55,};
	printf("empty, port:%u\n", getport(mac));

#endif

	/* find exist */
#if 0
	uint8_t mac0[6] = { 0xa1,  0xb1, 0xc1, 0x00, 0x00, 0x00,};
	uint8_t mac1[6] = { 0xff,  0x11, 0x22, 0x33, 0x44, 0x00,};
	uint8_t mac2[6] = { 0xa1,  0xb1, 0xc2, 0x00, 0x00, 0x00,};

	setport(mac0, 1);
	setport(mac1, 1);
	setport(mac2, 2);

	printf("exist, port:%u\n", getport(mac1));
	printf("exist, port:%u\n", getport(mac2));
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
#if 0
	uint16_t i = 0, n;
	union {
		uint16_t number;
		uint8_t mac[6];
		
	} mac_auto1;

	for (i = 0; i < 5; i++)
		mac_auto1.mac[i] = 0;


#define PORT(i)	((i & 0x1) ? 1 : 2)
	for (i = 0; i < 2000 ;i ++){
		setport(mac_auto1.mac, PORT(i));
		mac_auto1.number++;
	}

	mac_auto1.number = 0;
	for (i = 0; i < 2000 ;i ++){
		if (getport(mac_auto1.mac) != PORT(i))
			n++;
			mac_auto1.number++;
	}
	printf("n:%u\n", n);
#endif

	/* check autoremove 2*/
#if 1
	uint16_t i = 0, n;
	union {
		uint16_t number;
		uint8_t mac[6];
		
	} mac_auto1;

	for (i = 0; i < 5; i++)
		mac_auto1.mac[i] = 0;

#define PORT(i)	((i & 0x1) ? 1 : 2)
	for (i = 0; i < 2000 ;i ++){
		setport(mac_auto1.mac, PORT(i));
		if (getport(mac_auto1.mac) != PORT(i))
			n++;
			mac_auto1.number++;
	}

	printf("n:%u\n", n);
#endif
}

#endif
