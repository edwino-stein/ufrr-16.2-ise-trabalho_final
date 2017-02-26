#if !defined  _PUSHBUTTON
    #define _PUSHBUTTON

    #include <Arduino.h>

    #if !defined _CONFIG
        #define BTN_DELAY_ON_FALL 10
        #define BTN_PRESS_MARGIN 50
    #endif

    void initPushButton(int pin, void (*intCallback)(), void (*fallCallback)(int));
    void pushButtonListener();
    bool isPushButtonPresseted();

#endif
