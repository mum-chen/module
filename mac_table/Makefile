obj-m := kmactable.c                   #要生成的模块名     
modules-objs:= mymod.o        #生成这个模块名所需要的目标文件

KDIR := /lib/modules/`uname -r`/build   

PWD := $(shell pwd)

kernel:
	make -C $(KDIR) M=$(PWD) modules

default:
	gcc main.c umactable.c -o test

clean:
	rm -rf *.o .cmd *.ko *.mod.c .tmp_versions
