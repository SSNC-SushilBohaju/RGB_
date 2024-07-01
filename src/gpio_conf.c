#include "../lib/gpio_conf.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

volatile unsigned *gpio;

unsigned long get_gpio_base_address() {
    struct stat stat_buf;
    if (stat("/proc/device-tree/soc/ranges", &stat_buf) == 0) {
        FILE *fp = fopen("/proc/device-tree/soc/ranges", "rb");
        if (fp) {
            unsigned char buf[4];
            fseek(fp, 4, SEEK_SET); // Skip the first 4 bytes
            if (fread(buf, 1, sizeof(buf), fp) == sizeof(buf)) {
                fclose(fp);
                if (buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x00 && buf[3] == 0x20) {
                    return GPIO_BASE_PI_1; // Raspberry Pi 1
                } else if (buf[0] == 0x3F) {
                    return GPIO_BASE_PI_2_3_4; // Raspberry Pi 2, 3, or 4
                }
            }
        }
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
