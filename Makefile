ifeq ($(strip $(MODULE)),)
	obj-m += src/null_pointer.o
else
	obj-m += $(MODULE).o
endif


KERNEL_SRC = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean

image:
	docker build -t build_kernel .
