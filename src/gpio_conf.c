#include "../lib/gpio_conf.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#define HIGH 1
#define LOW 0

#define GPIO_BASE_PI_1 0x20000000
#define GPIO_BASE_PI_2_3 0x3F200000
#define GPIO_BASE_PI_4 0xFE200000

#define GPIO_SET *(gpio + 7)  // GPSET0
#define GPIO_CLR *(gpio + 10) // GPCLR0
#define GPIO_LEV *(gpio + 13) // GPLEV0

volatile unsigned *gpio;



unsigned long get_gpio_base_address() {
    // Check /proc/cpuinfo for model information
    FILE *fp_cpuinfo = fopen("/proc/cpuinfo", "r");
    if (fp_cpuinfo) {
        char line[256];
        while (fgets(line, sizeof(line), fp_cpuinfo)) {
            if (strncmp(line, "Model", 5) == 0) {
                if (strstr(line, "Raspberry Pi 3 Model B") || strstr(line, "Raspberry Pi 2 Model B")) {
                    fclose(fp_cpuinfo);
                    return GPIO_BASE_PI_2_3;
                } else if (strstr(line, "Raspberry Pi 1 Model B")) {
                    fclose(fp_cpuinfo);
                    return GPIO_BASE_PI_1;
                } else if (strstr(line, "Raspberry Pi 4 Model B")) {
                    fclose(fp_cpuinfo);
                    return GPIO_BASE_PI_4;
                }
            }
        }
        fclose(fp_cpuinfo);
    } else {
        fprintf(stderr, "Failed to open /proc/cpuinfo\n");
    }

    fprintf(stderr, "Error: Unable to determine Raspberry Pi model.\n");
    exit(EXIT_FAILURE);
}

void gpio_setup(int red_pin, int green_pin, int blue_pin,unsigned long gpio_base)
{
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0)

    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    gpio = (volatile unsigned *)mmap(
        NULL,
        4096,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        gpio_base);

    if (gpio == MAP_FAILED)
    {
        perror("mmap");
        close(mem_fd);
        exit(EXIT_FAILURE);
    }

    close(mem_fd);

    // Set RED_PIN to output
    *(gpio + (red_pin / 10)) &= ~(7 << ((red_pin % 10) * 3));
    *(gpio + (red_pin / 10)) |= (1 << ((red_pin % 10) * 3));

    // Set GREEN_PIN to output
    *(gpio + (green_pin / 10)) &= ~(7 << ((green_pin % 10) * 3));
    *(gpio + (green_pin / 10)) |= (1 << ((green_pin % 10) * 3));

    // Set BLUE_PIN to output
    *(gpio + (blue_pin / 10)) &= ~(7 << ((blue_pin % 10) * 3));
    *(gpio + (blue_pin / 10)) |= (1 << ((blue_pin % 10) * 3));
}

void gpio_port_write(int pin, uint8_t value)
{
    if (value == LOW) {
        GPIO_SET = (1 << pin);
    } else {
        GPIO_CLR = (1 << pin);
    }
}
