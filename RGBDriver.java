public class RGBDriver {
    static{
        System.loadLibrary("rgb");
    }
    public native void setLedColor(int pin, byte state);
    public native void clearColor(int pin);
}

