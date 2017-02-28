#include "serialListener.h"

void (*serialCallback)(byte[], short int) = NULL;

void initSerialListener(void (*callback)(byte[], short int)){
    serialCallback = callback;
}

void serialListener(){
    if(serialCallback == NULL) return;
    if(!Serial.available()) return;

    byte buffer[SERIAL_READ_BUFFER];
    short int lenght = Serial.readBytes(buffer, SERIAL_READ_BUFFER);
    delay(50);
    serialCallback(buffer, lenght);
}
