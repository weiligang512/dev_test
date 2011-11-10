#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<linux/fb.h>

#define FB_DEVICE "/dev/fb0"

int main(int argc, char * argv[])
{
	int fd;
	struct fb_var_screeninfo fb_var;
	char *fb_mem;
                
	fd = open(FB_DEVICE, O_RDWR);
	if(fd < 0) 
        {
		fprintf(stderr, "Errer open file %s: %s\n", FB_DEVICE, strerror(errno));
		exit(1);
	}
	
	if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0)
        {
		fprintf(stderr, "Error ioctl: %s\n", strerror(errno));
		exit(1);
	}
        
	printf("w = %d, h = %d, bpp = %d\n", fb_var.xres, fb_var.yres, fb_var.bits_per_pixel);
        
	if((fb_mem = mmap(NULL, (fb_var.xres * fb_var.yres
         * fb_var.bits_per_pixel/ 8), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == NULL)  {
		fprintf(stderr, "Error mmap file %s: %s\n", FB_DEVICE, strerror(errno));
		exit(1);
	}
 
	fprintf(stdout, "mmap file %s:Success Usr Address 0x%x\n", FB_DEVICE, (int)fb_mem);
        
       munmap(fb_mem , fb_var.xres * fb_var.yres * fb_var.bits_per_pixel/ 8);
        
	close(fd);
	
	return 0;
}
