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
	
	GPIOCALTFN0 &= ~(3<<26);//gpio c13
	GPIOCALTFN0 |= (2<<26);//function2
	GPIOCOUTENB |= (1<<13);

	GPIOCALTFN0 &= ~(3<<28);//gpio c14
	GPIOCALTFN0 |= (2<<28);//function2
	GPIOCOUTENB |= (1<<14);
	
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
	#define TIMERTCFG0 *(unsigned int *)base_pwm
	#define TIMERTCFG1 *(unsigned int *)(base_pwm+0x04)
	#define TIMERTCON *(unsigned int *)(base_pwm+0x08)
	#define TIMERTCNTB1 *(unsigned int *)(base_pwm+0x18)
	#define TIMERTCMPB1 *(unsigned int *)(base_pwm+0x1C)
	#define TIMERTCNTO1 *(unsigned int *)(base_pwm+0x20)
	#define TIMERTCNTB2 *(unsigned int *)(base_pwm+0x24)
	#define TIMERTCMPB2 *(unsigned int *)(base_pwm+0x28)
	#define TIMERTCNTO2 *(unsigned int *)(base_pwm+0x2C)
	
	TIMERTCFG0 &= ~(255<<8);//prescaler 0
	TIMERTCFG0 &= ~(255<<0);
	TIMERTCFG1 &= ~(15<<0);
	TIMERTCFG1 &= ~(15<<4);//divider 1
	TIMERTCFG1 &= ~(15<<8);
	TIMERTCNTB1 =66000;//setting cnt
	TIMERTCMPB1 =16000;//setting compare
	TIMERTCNTB2 =66000;//setting cnt
	TIMERTCMPB2 =6000;//setting compare  this munber is biger ,and the average U is high
	TIMERTCON  |=  (1<<11);
	TIMERTCON  |=  (1<<15);
	TIMERTCON  |=  (1<<8);//start pwm
	TIMERTCON  |=  (1<<12);//start pwm
	 
	
}
void pwm_uninit(void)
{
	TIMERTCON  &=  ~(255<<8);//close pwm
	if(dev_fd_pwm)
        close(dev_fd_pwm);
   	munmap((unsigned int *)base_pwm,MAP_SIZE);
}
