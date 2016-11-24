#include <linux/init.h>
#include <linux/module.h>
/*******************************************************************************
 * include segement
*******************************************************************************/
#include "mactable.h"
#ifdef __KERNEL__
#  include <linux/string.h>
#  include <linux/slab.h>
#  include <linux/bug.h>
#  include <linux/kernel.h>
#else
#  include <string.h>
#  include <stdio.h>
#  include <stdlib.h>
#  include <assert.h>
#  define BUG_ON(x)	assert(!(x))
#  define kmalloc(x, f)	malloc(x)
#  define kfree(x)	free(x)
#endif

/*******************************************************************************
 * function declare
*******************************************************************************/
/* public */
int mactable_init(void);
void mactable_exit(void);
uint8_t mactable_getport(uint8_t *mac);
void mactable_setport(uint8_t *mac, uint8_t port);

/* private */
static bool find(uint8_t mac[], uint16_t *result);
static uint16_t hashcode(uint8_t mac[], uint16_t times);
/*******************************************************************************
 * global variable declare
*******************************************************************************/

/*******************************************************************************
 * private variable declare
*******************************************************************************/
static struct mac_ctr	*controller;
static struct mac_field	*mactable;

/*******************************************************************************
 * private function
*******************************************************************************/

static inline bool maccmp(uint8_t *mac1, uint8_t *mac2)
{
	int i = 0;
	for (i = 0; i < 6; i++)
		if (mac1[i] != mac2[i])
			return false;
	return true;
}

/*------- hash function --------------------------------------------------------
 *   Makeing hash table in a static array, so I use the double-hash
 *       h(k, i) =(h1(k), i*h2(k))%m
 *   For the reason that we can loop every item in the table in the worst case.
 * We can set the m(total num) is power of 2, and let the function h2 always
 * return an odd number.
--------- hash function ------------------------------------------------------*/
/*
 * @Function:	ELF hash (h1 in doubel hash)
 * --------------------
 * @Desc:	
 *
 * @Param:	
 *
 *  mac:	
 *
 * @Return:	
 */
static uint64_t ELF(uint8_t *mac)
{
	uint64_t hash = 0,x = 0;
	unsigned char i = 0;

	for (i = 0 ; i < 6; i++) {
		hash = (hash << 4) + CHAR_AT_MAC(mac, i);
		if ((x= hash & 0xF0000000) != 0)
			hash ^= (x >> 24);
		hash &= ~x;
	}
	return hash;
}

/*
 * @Function:	BKDR hash (h2 in doubel hash)
 * --------------------
 * @Desc:	
 *
 * @Param:	
 *
 *  mac:	
 *
 * @Return:	
 */
static uint64_t BKDR(uint8_t *mac)
{
	uint64_t seed = 131;
	uint64_t hash = 0;
	unsigned char i = 0;
	for (i = 0; i < 6; i++)
		hash = (hash * seed) + CHAR_AT_MAC(mac, i);
		
	return hash | 0x01; /* we need this function always return odd number. */
}

/*
 * @Function:	hashcode
 * --------------------
 * @Desc:	generate hash code with the method double-hash(h1:ELF & h2:BKDR).
 *
 * @Param:	
 *
 *  mac:	the mac number, expect 48-bit, but this function deal with 
 *		all number in fact.
 *
 *  times:	conflict times
 *
 * @Return:	the hash code is equal to the index of mac-field
 */
static uint16_t hashcode(uint8_t *mac, uint16_t times)
{
	uint64_t hash;
	uint16_t idx;
	if (times)
		hash = ELF(mac) + BKDR(mac) * times;
	else
		hash = ELF(mac);

	idx = hash & 0x7ff; /* mod 2^11 */

	return idx;
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
static bool find(uint8_t *mac, uint16_t *result)
{
	struct mac_field *field = NULL;
	uint16_t idx = 0xffff, first;

	/* control flage */
	unsigned char times = 0, setept = false;
	/* record empty mac_field(first delete) */
	uint16_t empty = 0xffff;
	
	/* get the field */
	idx = hashcode(mac, times);
	first = idx;
	field = &mactable[idx];

	do{
		/* find */
		if (field->used == FIELD_USED && maccmp(field->mac, mac)){
			*result = idx;
			return true;
		}

		/* not find:(field->used == FIELD_DELETED || field->mac != mac) */
		times++;
		if (!setept && field->used == FIELD_DELETED){
			empty = idx;
			setept = true;
		}
		idx = hashcode(mac, times);
		field = &mactable[idx];
	} while (field->used != FIELD_EMPTY && idx != first);

	/* always not find */
	if (!setept)
		empty = idx;
	*result = empty;
	return false;
}

static void autoremove(uint16_t number)
{
	uint16_t i = 0;
	struct mac_field *field = NULL;
	for (i = 0; i < number; i++) {
		field = &mactable[controller->head];
		if (field->used != FIELD_USED) {
			PDEBUG("error: autoremove mac-table case not used field\n");
			return ;
		}
		controller->head = field->next;
		field->used = FIELD_DELETED;
		controller->num--;
	}
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
 * * @Return:	
 */
void mactable_setport(uint8_t *mac, uint8_t port)
{
	uint16_t aim_idx = 0xffff;
	bool ret = find(mac, &aim_idx);

	uint8_t tag = port & 0x3;
#if 0 // debug
	PDEBUG("mac:%x, aim_idx in _setport:%u\n",field->mac, aim_idx); 
#endif

	struct mac_field *aim = &mactable[aim_idx];
	/* aim exist */
	if (ret) {
		aim->tag = tag;
		return;
	}
	/* aim not find */
	memcpy(aim->mac, mac, sizeof(uint8_t)*6);
	aim->tag = tag;
	aim->used = FIELD_USED;
	
	mactable[controller->tail].next = aim_idx;
	controller->tail = aim_idx;

	if (controller->num == 0)
		controller->head = aim_idx;
	else if (controller->num >= VALID_TABLE_LENGTH)
		autoremove(AUTO_REMOVE);

	controller->num++;

#if 0
	PDEBUG("head:%u, tail:%u, number:%u\n",
			controller->head, controller->tail, controller->num);
#endif
}
EXPORT_SYMBOL(mactable_setport);

uint8_t mactable_getport(uint8_t *mac)
{
	struct mac_field field;

	uint16_t aim_idx = 0xffff;
	bool ret = find(mac, &aim_idx);
	
	if (ret) {
		struct mac_field *aim = &mactable[aim_idx];
		return aim->tag;
	} else {
		return TAG_UNUSED;
	}
}
EXPORT_SYMBOL(mactable_getport);

int mactable_init(void)
{
	int ret = 0;
	/* init mactable */
	mactable = (struct mac_field *)kmalloc(sizeof(struct mac_field) * TABLE_LENGTH, GFP_KERNEL);
	memset(mactable, 0, sizeof(struct mac_field) * TABLE_LENGTH);

	/* init mac_controller */
	controller = (struct mac_ctr*)kmalloc(sizeof(struct mac_ctr), GFP_KERNEL);
	memset(mactable, 0, sizeof(struct mac_ctr));
	
	controller->num = 0;
	controller->max = VALID_TABLE_LENGTH;


	return ret;
}
EXPORT_SYMBOL(mactable_init);

void mactable_exit(void)
{
	kfree(controller);
	kfree(mactable);
}
EXPORT_SYMBOL(mactable_exit);

/*******************************************************************************
 * module information
*******************************************************************************/
#ifdef MAC_TABLE_MODULE
module_init(mactable_init);
module_exit(mactable_exit);
#endif
