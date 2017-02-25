#include "rfidController.h"
#include <MFRC522.h>

MFRC522 *rfidSensor;
void (*rfidCallback)(String) = NULL;
bool rfidReadEnabled;

void initRfidSensor(int sdaPin, int rstPin, void (*cb)(String)){
    rfidSensor = new MFRC522(sdaPin, rstPin);
    rfidCallback = cb;
    rfidReadEnabled = true;
    rfidSensor->PCD_Init();
}

void rfidListener(){

    if(rfidCallback == NULL || !rfidReadEnabled) return;
    if (!rfidSensor->PICC_IsNewCardPresent()) return;
    if (!rfidSensor->PICC_ReadCardSerial()) return;

    String uid= "";
    byte data;

    for (byte i = 0; i < rfidSensor->uid.size; i++) {
        uid.concat(String(rfidSensor->uid.uidByte[i] < 0x10 ? " 0" : " "));
        uid.concat(String(rfidSensor->uid.uidByte[i], HEX));
    }

    uid.toUpperCase();
    rfidCallback(uid);
}

void disableRfidReader(bool disable){
    rfidReadEnabled = !disable;
}

bool isEnableRfidReader(){
    return rfidReadEnabled;
}
