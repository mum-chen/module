#ifndef _MAC_TABLE_H_
#define _MAC_TABLE_H_

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifdef KERNEL_BUILD
#include <linux/types.h>
#else
typedef unsigned short	uint16_t;
typedef unsigned long	uint64_t;
typedef unsigned char	bool;
#endif




#define TABLE_LENGTH	2048

#ifndef TABLE_USEING_RATE
#define TABLE_USEING_RATE	0.8
#endif

#define VALID_TABLE_LENGTH	(TABLE_LENGTH * TABLE_USEING_RATE)



#define CHAR_AT_MAC(mac, n)	(((0xff << 8 * n) & mac) >> 8 * n)

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
	
	uint16_t num:11;
	uint16_t resv4:5;
};

struct mac_field {
	uint64_t mac:48;
	uint64_t resv1:16;
	uint16_t tag:2;
	uint16_t used:1;
	uint16_t resv2:2;
	uint16_t next:11; /* max length is 2048 2^11 */
	uint16_t resv3:5;
	uint16_t lnext:11; /* max length is 2048 2^11 */
};


/*******************************************************************************
 * export function
*******************************************************************************/
extern int mactable_init();
extern void mactable_exit();
extern unsigned char getport(long mac);
extern void setport(long mac, unsigned char port);

#endif /* _MAC_TABLE_H_ */
