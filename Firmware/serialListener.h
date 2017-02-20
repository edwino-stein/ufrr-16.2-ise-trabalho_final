#if !defined  _SERIAL_LISTENER
    #define _SERIAL_LISTENER

    #include <Arduino.h>

    #if !defined _CONFIG
        #define SERIAL_READ_BUFFER 64
    #endif

    void initSerialListener(void (*callback)(byte[], short int));
    void serialListener();

#endif
