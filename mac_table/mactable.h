
/*******************************************************************************
 *
*******************************************************************************/
#ifndef _MAC_TABLE_H_
#define _MAC_TABLE_H_

/*******************************************************************************
 * macro type/constant
*******************************************************************************/
#ifdef KERNEL_BUILD
#include <linux/types.h>
#else
typedef unsigned short	uint16_t;
typedef unsigned long	uint64_t;
typedef unsigned char	bool;
#endif

#define true 1
#define false 0

#define FIELD_USED	2
#define FIELD_EMPTY	0
#define FIELD_DELETED	1

#define TAG_PORT_5	2
#define TAG_PORT_6	1
#define TAG_UNUSED	0
#define TAG_UNUSED_1	3

#define TABLE_LENGTH	2048
#define TABLE_USEING_RATE	0.8
#define VALID_TABLE_LENGTH	(TABLE_LENGTH * TABLE_USEING_RATE)

#define AUTO_REMOVE	1

/*******************************************************************************
 * macro function
*******************************************************************************/

#define CHAR_AT_MAC(mac, n)	(((0xff << 8 * n) & mac) >> 8 * n)

/*******************************************************************************
 * struct define
*******************************************************************************/
/*
 * @Struct:	mac_ctr
 *		mac-table controller
 * --------------------
 * @head:	the head of mac-table in linked-hash
 * @resv1:	reserve
 * @tail:	the end of mac-table in linked-hash
 * @resv2:	reserve
 * @max:	the 
 * @resv3:	reserve
 * @num:	the number of the table already used
 * @resv4:	reserve
 */
struct mac_ctr {
	uint16_t head:11;
	uint16_t resv1:5;

	uint16_t tail:11;
	uint16_t resv2:5;

	uint16_t max:11;
	uint16_t resv3:5;
	
	uint16_t num:12;
	uint16_t resv4:4;
};

/*
 * @Struct:	mac_field
 *		mac-table field
 * --------------------
 * @mac:	the head of mac-table in linked-hash
 * @tag:	record the source/forward port.
 * @used:	did the field is used?
 * @resv:	reserve
 * @next:	the next field in the table, in order to record the queue,
		for dropping when the hash-table is full.
 */
struct mac_field {
	uint64_t mac:48;
	uint16_t tag:2;
	uint16_t used:2;
	uint16_t resv:1;
	uint16_t next:11; /* max length is 2048 2^11 */
};


/*******************************************************************************
 * export function
*******************************************************************************/
extern int mactable_init();
extern void mactable_exit();
extern unsigned char getport(uint64_t mac);
extern void setport(uint64_t mac, unsigned char port);

#ifdef DEBUG
void sizeofstruct(void);
void debug_find(void);
#endif

#endif /* _MAC_TABLE_H_ */
