#include <jni.h>
#include <unistd.h> // For usleep
#include "Main.h"
#include "lib/rgb_driver.h"

JNIEXPORT void JNICALL Java_Main_gpioSetup(JNIEnv *env, jobject obj, jint redPin, jint greenPin, jint bluePin, jlong gpioBase) {
    gpio_setup(redPin, greenPin, bluePin, gpioBase);
}

JNIEXPORT jlong JNICALL Java_Main_getGpioBaseAddress(JNIEnv *env, jobject obj) {
    return (jlong)get_gpio_base_address();
}

JNIEXPORT void JNICALL Java_Main_setLedColor(JNIEnv *env, jobject obj, jint pin, jbyte state) {
    set_led_color(pin, state);
}

JNIEXPORT void JNICALL Java_Main_clearColor(JNIEnv *env, jobject obj, jint pin) {
    clear_color(pin);
}

JNIEXPORT void JNICALL Java_Main_usleep(JNIEnv *env, jobject obj, jint microseconds) {
    usleep(microseconds);
}
