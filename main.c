#include "lib/rgb_driver.h"

#define red_pin 17
#define green_pin 27
#define blue_pin 22

int main()
{

    unsigned long gpio_base = get_gpio_base_address();
    gpio_setup(red_pin, green_pin, blue_pin, gpio_base);


    /**
     * For blinking Green light
     * For Green High
     */
    set_led_color(red_pin, LOW);
    set_led_color(green_pin, HIGH);
    set_led_color(blue_pin, LOW);
    usleep(500000);
    /**
     * For Green Low
     */
    // set_led_color(red_pin, LOW);
    // set_led_color(green_pin, LOW);
    // set_led_color(blue_pin, LOW);
    // usleep(500000);

    clear_color(green_pin);
    clear_color(red_pin);
    clear_color(blue_pin);

    return EXIT_SUCCESS;
}