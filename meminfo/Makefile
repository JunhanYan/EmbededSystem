obj-m := mymeminfomodule.o
mymeminfomodule-objs:= mymeminfo.o
KERNELDIR := /lib/modules/$(shell uname -r)/build                                                               
PWD := $(shell pwd)  
  
default:  
	make -C $(KERNELDIR) M=$(PWD) modules  
  
clean:  
	make -C $(KERNELDIR) M=$(PWD) clean  
