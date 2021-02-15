obj-m := xxx.o
PWD := $(shell pwd)
KERNELDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	@rm -rf .*.swp *.swp *.order .*.cmd *.ko *.mod *.mod.c *.o *.symvers
