

#CC = gcc
CC = aarch64-linux-gnu-gcc
export CC
Dist = ./firmware

all:
	cd sys_init && $(MAKE)
	cd sys_usbFPGA && $(MAKE)
	cd sys_config && $(MAKE)
	cd sys_algorithm && $(MAKE)
#	cd sys_internet && $(MAKE)
#	cd sys_storedb 	&& $(MAKE)

clean:
	cd sys_init && $(MAKE) clean
	cd sys_usbFPGA && $(MAKE) clean
	cd sys_config && $(MAKE) clean
	cd sys_algorithm && $(MAKE) clean
#	cd sys_internet && $(MAKE) clean
#	cd sys_storedb && $(MAKE) clean

install:
	mv sys_init/sysinit $(Dist)
	mv sys_usbFPGA/sysusbFPGA $(Dist)
	mv sys_config/sysconfig $(Dist)
	mv sys_algorithm/sysalgorithm $(Dist)
#	mv sys_internet/sysinternet $(Dist)
#	mv sys_storedb/sysstoredb $(Dist)
	
