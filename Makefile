ifeq ($(strip $(MODULE)),)
	obj-m += hello_simple.o
else
	obj-m += $(MODULE).o
endif


KERNEL_SRC = /lib/modules/$(shell uname -r)/build 

all:
	make -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean
