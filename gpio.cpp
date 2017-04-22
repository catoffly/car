#include "car.hpp"
#include  "gpio.hpp"
#define GPIOC_BASE_ADDRESS   (0xC001C000)
#define MAP_SIZE 40
static int dev_fd;

void gpio_init(void)
{
    dev_fd = open("/dev/mem", O_RDWR | O_NDELAY);
    if (dev_fd < 0)
    {
        printf("open(/dev/mem) failed.");
       
    }
    unsigned int base = (unsigned int)mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, dev_fd, GPIOC_BASE_ADDRESS );
    #define GPIOCOUT *(unsigned int *)base
    #define GPIOCOUTENB *(unsigned int *)(base+0x04)
    #define GPIOCALTFN0 *(unsigned int *)(base+0x20)
    GPIOCALTFN0 &= ~(3<<26);
    GPIOCALTFN0 |= (1<<26);
    GPIOCOUTENB |= (1<<13);
    GPIOCOUT |= (1<<13);
    sleep(1);
    GPIOCOUT &= ~(1<<13);
sleep(1);
    if(dev_fd)
        close(dev_fd);
    munmap((unsigned int *)base,MAP_SIZE);
    
}
