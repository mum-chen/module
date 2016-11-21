#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

#include "mactable.h"



static int mactable_init(void)
{
	printk(KERN_ALERT "Hello, world contro:%d, mac_field:%d \n",
		sizeof(_controller), sizeof(mac_field));
	return 0;
}
static void mactable_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
