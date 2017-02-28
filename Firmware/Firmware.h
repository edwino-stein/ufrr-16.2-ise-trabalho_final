#if !defined  _FIRMWARE
    #define _FIRMWARE

/* ******************************** CALLBACKS ********************************* */

    void onInterruptTime();
    void onRFIDReceive(String uid);
    void onInterruptBtn();
    void onPressingBtn(int pressTime);
    void onSerialReceive(byte* data, short int length);

/* *********************************** UTIL *********************************** */

    void enableRFIDRecordMode(bool enable);
    void enableServerFoodMode(bool enable);
    void serve();
    char * floatToString(float value);
    unsigned long parseServeFoodTime (byte data);

#endif
