#ifndef _GPIO_CONF_H__
#define _GPIO_CONF_H__

#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#define HIGH 1
#define LOW 0

#define GPIO_BASE_PI_1 0x20000000
#define GPIO_BASE_PI_2_3_4 0x3F200000

#define GPIO_SET *(gpio + 7)  // GPSET0
#define GPIO_CLR *(gpio + 10) // GPCLR0
#define GPIO_LEV *(gpio + 13) // GPLEV0

unsigned long get_gpio_base_address(); 
void gpio_setup(int red_pin, int green_pin, int blue_pin,unsigned long gpio_base);
void gpio_port_write(int pin, uint8_t value);



#endif
