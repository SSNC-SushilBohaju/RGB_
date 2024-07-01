#include "lib/rgb_driver.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <red_pin> <green_pin> <blue_pin>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Define LED pins (BCM pin numbers) from command line arguments
    int red_pin = atoi(argv[1]);
    int green_pin = atoi(argv[2]);
    int blue_pin = atoi(argv[3]);

    unsigned long gpio_base = get_gpio_base_address();
    gpio_setup(red_pin, green_pin, blue_pin, gpio_base);
    srand(time(NULL)); // Initialize random number generator

    while (1)
    {
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
        set_led_color(red_pin, LOW); 
        set_led_color(green_pin, LOW); 
        set_led_color(blue_pin, LOW); 
        usleep(500000);


    }

    return EXIT_SUCCESS;
}