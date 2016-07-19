linux_device_drivers_tutorial
=============================

Linux Device Drivers Tutorial

Hi, this is a compendium of multiple didactic Linux Kernel modules, I am doing
this due to the fact that many times somebody say that the LDD book is too
complicated, well here is a series of examples that might be helpful. 

In my opinion a really good start for really newbies Linux Modules Developers
WAS (past time on purpose) The Linux Kernel Module Programming Guide
(http://www.tldp.org/LDP/lkmpg/2.6/html/). However this guide is based on the
Kernel 2.6.. which has many deprecated parts in relationship with the 3.~
kernel 

Well this project tries to update the source code of that guide to the  latest
version of the kernel (please update and improve as possible), hopefully if
many folks agree the guide will be updated, just as its authors wanted. 


SET UP: 

Download all the kernel dev packages (in case of Fedora):

    https://fedoraproject.org/wiki/Building_a_custom_kernel

You might have some problems with the livna.repo, please temporary remove it


BUILD:

    1) make MODULE="<name_of_module>" // DO NOT add the .c, just the name of
    the module. If no name is passed the makefile will build the basic hello
    world module

    2)  make clean : will clean the module

INSTALL:

    insmod module.ko
    modprobe module.ko

REMOVE:

    rmmod module

Check printk message: 
    
    dmesg
    or
    cat /var/log/syslog
    
