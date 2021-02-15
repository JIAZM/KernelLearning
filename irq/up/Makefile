obj-m := interrupt.o
PWD := $(shell pwd)
KERNELDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	@rm -rf *.o *.mod.c *.mod.o *.ko *.order Module.* *.mod .*.cmd
