# RGB_Driver_RPI

Process to compile

1) sudo gcc -shared -o librgb.so -fPIC jni_rgb_driver.c -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -I./lib src/gpio_conf.c src/rgb_driver.c

To run

1) sudo java -Djava.library.path=. Main

Note: Check JAVA_HOME dir . If not set, Please kindly export JAVA_HOME inside bashrc 

