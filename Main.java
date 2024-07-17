public class Main {

    // Declare the native methods
    public static native void gpioSetup(int redPin, int greenPin, int bluePin, long gpioBase);
    public static native long getGpioBaseAddress();
    public static native void setLedColor(int pin, byte state);
    public static native void clearColor(int pin);
    public static native void usleep(int microseconds);

    // Load the native library
    static {
        System.loadLibrary("rgb"); // The library name without platform-specific prefix/suffix
    }

    public static void main(String[] args) {
        int redPin = 17;
        int greenPin = 27;
        int bluePin = 22;

        long gpioBase = getGpioBaseAddress();
        gpioSetup(redPin, greenPin, bluePin, gpioBase);

        // For blinking Green light
        // For Green High
        setLedColor(redPin, (byte) 0); // LOW
        setLedColor(greenPin, (byte) 1); // HIGH
        setLedColor(bluePin, (byte) 0); // LOW
        usleep(500000);

        // For Green Low
        // setLedColor(redPin, (byte) 0); // LOW
        // setLedColor(greenPin, (byte) 0); // LOW
        // setLedColor(bluePin, (byte) 0); // LOW
        // usleep(500000);

        clearColor(greenPin);
        clearColor(redPin);
        clearColor(bluePin);
    }
}
