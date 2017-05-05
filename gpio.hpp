#ifndef GPIO_H
#define GPIO_H

#include "car.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


#define GPIOC_BASE_ADDRESS   (0xC001C000)
#define PWM_BASE_ADDRESS     (0xc0018000)
#define MAP_SIZE 40


using namespace cv;
void gpio(void);
void gpio_init(void);
void gpio_uninit(void);
void gpio_high(void);
void gpio_low(void);
void pwn_init(void);
void pwm_uninit(void);
#endif
