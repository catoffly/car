#include "car.hpp"
#include  "gpio.hpp"


static int dev_fd,dev_fd_pwm;
unsigned int base,base_pwm;
void gpio(void)
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
    GPIOCALTFN0 &= ~(3<<14);
    GPIOCALTFN0 |= (1<<14);
    GPIOCOUTENB |= (1<<7);
    GPIOCOUT |= (1<<7);
    sleep(1);
    GPIOCOUT &= ~(1<<7);
sleep(1);
    if(dev_fd)
        close(dev_fd);
    munmap((unsigned int *)base,MAP_SIZE);
    
}
void gpio_init(void)
{
	dev_fd = open("/dev/mem", O_RDWR | O_NDELAY);
	if (dev_fd < 0)
	{
	printf("open(/dev/mem) failed.");

	}
	 base = (unsigned int)mmap(NULL, MAP_SIZE, PROT_READ | 	PROT_WRITE, MAP_SHARED, dev_fd, GPIOC_BASE_ADDRESS );
	#define GPIOCOUT *(unsigned int *)base
	#define GPIOCOUTENB *(unsigned int *)(base+0x04)
	#define GPIOCALTFN0 *(unsigned int *)(base+0x20)
	GPIOCALTFN0 &= ~(3<<14);//gpio c7
	GPIOCALTFN0 |= (1<<14);
	GPIOCOUTENB |= (1<<7);
	//GPIOCOUT &= ~(1<<7);
	GPIOCOUT |= (1<<7);
	GPIOCALTFN0 &= ~(3<<18);//gpio c9
	GPIOCALTFN0 |= (1<<18);
	GPIOCOUTENB |= (1<<9);
	//GPIOCOUT &= ~(1<<8);
	GPIOCOUT |= (1<<9);
}

void gpio_uninit(void)
{
	if(dev_fd)
        close(dev_fd);
   	munmap((unsigned int *)base,MAP_SIZE);
}
void gpio_high(void)
{
	GPIOCOUT |= (1<<7);
	GPIOCOUT |= (1<<9);
}
void gpio_low(void)
{	
	GPIOCOUT &= ~(1<<7);
	GPIOCOUT &= ~(1<<9);
}


void pwn_init(void)
{
	dev_fd_pwm = open("/dev/mem", O_RDWR | O_NDELAY);
	if (dev_fd_pwm < 0)
	{
	printf("open(/dev/mem) failed.");

	}
	 base_pwm = (unsigned int)mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, dev_fd_pwm, PWM_BASE_ADDRESS );
	#define GPIOCOUT *(unsigned int *)base
	#define GPIOCOUTENB *(unsigned int *)(base+0x04)
	#define GPIOCALTFN0 *(unsigned int *)(base+0x20)
	GPIOCALTFN0 &= ~(3<<14);//gpio c7
	GPIOCALTFN0 |= (1<<14);
	GPIOCOUTENB |= (1<<7);
	//GPIOCOUT &= ~(1<<7);
}
