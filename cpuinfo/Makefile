obj-m := mycpustatmodule.o
mycpustatmodule-objs:= mycpuinfo.o
KERNELDIR := /lib/modules/$(shell uname -r)/build                                                               
PWD := $(shell pwd)  
  
default:  
	make -C $(KERNELDIR) M=$(PWD) modules  
  
clean:  
	make -C $(KERNELDIR) M=$(PWD) clean  
