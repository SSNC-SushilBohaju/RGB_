# RGB_Driver_RPI

Process to compile

1) sudo gcc -shared -o librgb.so -fPIC jni_rgb_driver.c -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -I./lib src/gpio_conf.c src/rgb_driver.c
  -- This will create librgb share library and Main.class, copy librgb.so file inside of /usr/lib directory

To run
1) sudo java -Djava.library.path=. Main

To create jar file
1)jar cvfm "filename".jar Manifest.txt Main.class
  -- sudo java -jar "filename".jar
 
Note: Check JAVA_HOME dir . If not set, Please kindly export JAVA_HOME inside bashrc 

