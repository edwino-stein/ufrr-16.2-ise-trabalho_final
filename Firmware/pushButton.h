#if !defined  _PUSHBUTTON
    #define _PUSHBUTTON

    #include <Arduino.h>

    #if !defined _CONFIG
        #define BTN_DELAY_ON_FALL 10
    #endif

    void initPushButton(int pin, void (*intCallback)(), void (*fallCallback)(int));
    void pushButtonListener();

#endif
