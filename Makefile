
obj-m += timer_simple.o
#obj-m += timer_hiresolution.o
#obj-m += jiffies_1.o

KERNEL_SRC = /lib/modules/$(shell uname -r)/build 

all:
	make -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean
