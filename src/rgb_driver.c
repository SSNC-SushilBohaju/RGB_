#include "../lib/rgb_driver.h"

void set_led_color(int pin, uint8_t state)
{
    gpio_port_write(pin, state);
}

void clear_color(int pin)
{
    set_led_color(pin, LOW);
    set_led_color(pin, LOW);
    set_led_color(pin, LOW);
}