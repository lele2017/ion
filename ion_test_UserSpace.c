#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "/home/developer/kernel3.4/goldfish/include/linux/ion.h"

void main()
{
    struct ion_fd_data fd_data;
    struct ion_allocation_data ionAllocData;
    ionAllocData.len=0x1000;
    ionAllocData.align = 0;
    ionAllocData.flags = ION_HEAP_TYPE_SYSTEM;

    int fd=open("/dev/ion",O_RDWR);
    ioctl(fd,ION_IOC_ALLOC, &ionAllocData);
    fd_data.handle = ionAllocData.handle;
    ioctl(fd,ION_IOC_SHARE,&fd_data); 
    int *p = mmap(0,0x1000,PROT_READ|PROT_WRITE,MAP_SHARED,fd_data.fd,0);
    p[0]=99;
    perror("test");
    printf("hello all %d\n",p[0]);
}
