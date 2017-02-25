#if !defined  _LEDBEHAVIOR
    #define _LEDBEHAVIOR

    #include <Arduino.h>

    #if !defined _CONFIG
        #define LED_ALIGHT 0
        #define LED_OFF 1
        #define LED_BLINKING 2
        #define LED_BLINKING_TIMER 100
        #define LED_BLINK_DELAY 10
    #endif

    void initLedBehavior(int pin);
    void ledListener();
    void setLedBehavior(int mode);

#endif
