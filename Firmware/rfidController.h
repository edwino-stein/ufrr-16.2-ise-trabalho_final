#if !defined  _RFID_COTROLLER
    #define _RFID_COTROLLER

    #include <Arduino.h>

    void initRfidSensor(int sdaPin, int rstPin, void (*callback)(String));
    void rfidListener();
    void disableRfidReader(bool disable);
    bool isEnableRfidReader();

#endif
