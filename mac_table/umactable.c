/*******************************************************************************
 * include segement
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "mactable.h"

/*******************************************************************************
 * function declare
*******************************************************************************/
/* public */
int mactable_init();
void mactable_exit();
unsigned char getport(long mac);
void setport(long mac, unsigned char port);

/* private */
static inline long getmac(long mac);
static inline int _setport(struct mac_field *mac);
static inline int _getport(struct mac_field *mac);
static uint16_t hashcode(struct mac_field mac);
/*******************************************************************************
 * global variable declare
*******************************************************************************/

/*******************************************************************************
 * private variable declare
*******************************************************************************/
static struct mac_ctr	*controller;
static struct mac_field	*mactable;

/*******************************************************************************
 * debug function
*******************************************************************************/
void sizeofstruct()
{
	printf("Hello, world contro:%ld, mac_field:%ld \n",
		sizeof(struct mac_ctr), sizeof(struct mac_field));
	
	printf("Hello, world p-contro:%ld, p-mac_field:%ld \n",
		sizeof(controller), sizeof(mactable));

	int a = VALID_TABLE_LENGTH;

	printf("vaild table number is %d\n", a);
}

/*******************************************************************************
 * private function
*******************************************************************************/
/*
 * @Function:	hashcode
 * --------------------
 * @Desc:	
 *
 * @Param:	
 *
 *  mac:	
 *
 * @Return:	
 */
static uint16_t hashcode(struct mac_field mac)
{
	unsigned long hash = 0;
	unsigned long x = 0;
	unsigned char i = 0, c;

	for (i; i < 6; i++) {
		hash = (hash << 4) + CHAR_AT_MAC(mac.mac, i);
		if ((x= hash & 0xF0000000) != 0)
			hash ^= (x >> 24);
		hash &= ~x;
	}
	return hash & 0x7ff;
}

static inline long getmac(long mac)
{
	return mac & 0xffffffffffff;
}

/*
 * @Function:	find
 * --------------------
 * @Desc:	find mac_field depend on mac-address
 *
 * @Param:	
 *  mac:	mac address, only get the last 48bit
 *  result:	return the find result
 *
 * @Return:	if find one field, then return true and the @result will point to that.
		else return false and the @result will point to an available idx.
 */
static bool *find(long mac, struct mac_field **result)
{
	int idx = hashcode(mac);
	
}

static newfield(mac_field *field)
{
	/* check the did the table is full */
	
	
	/* if full remove the head */

	/* aim */
}


static inline int _setport(struct mac_field *field)
{
	struct mac_field *aim = find(field->mac);
	
	if (aim){
		aim->tag = field->tag;
	} else {
		
		
	}

	return true;
}

static inline int _getport(struct mac_field *field)
{
	
	mac->tag = 3;
	return true;
}

/*******************************************************************************
 * public function
*******************************************************************************/
/*
 * @Function:	setport
 * --------------------
 * @Desc:	set mac-table by mac and port
 *
 * @Param:	
 *  mac:	only get the last 48bit
 *  port:	only get the last 2bit
 *
 * @Return:	
 */
void setport(long mac, unsigned char port)
{
	struct mac_field field = {
		.mac = getmac(mac),
		.tag = port & 0x3,
	};

	_setport(&field);
}

unsigned char getport(long mac)
{
	struct mac_field field = {
		.mac = getmac(mac),
	};

	int ret = _getport(&field);
	
	if (ret)
		return field.tag;
	else
		return 0xff; /* use magic number temporarily */
}

int mactable_init()
{
	int ret = 0;
	/* init mactable */
	mactable = (struct mac_field *)malloc(sizeof(struct mac_field) * TABLE_LENGTH);
	memset(mactable, 0, sizeof(struct mac) * TABLE_LENGTH);

	/* init mac_controller */
	controller = (struct mac_ctr*)malloc(sizeof(struct mac_ctr));
	memset(mactable, 0, sizeof(struct mac_ctr));
	
	controller->num = 0;
	controller->max = VALID_TABLE_LENGTH;


	return ret;
}

void mactable_exit()
{
	free(controller);
	free(mactable);
}
