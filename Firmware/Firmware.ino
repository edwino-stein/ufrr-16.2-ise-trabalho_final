#include "config.h"
#include <SPI.h>
#include <MsTimer2.h>

#include "rfidController.h"
#include "pushButton.h"
#include "ledBehavior.h"

/* **************** GLOABAL VARS **************** */

char PROG_FUNC = DO_NOTHING;
String currentUID;

/* **************** CALLBACKS **************** */

// Time
void onInterrupTime(){
    Serial.println("onInterrupTime");
}

// RFID
void onRFIDReceive(String uid){

    if(PROG_FUNC == RFID_REG){
        currentUID = uid;
        Serial.print("UID registrada: ");
        Serial.println(uid);
        enableRFIDRecordMode(false);
        return;
    }

    if(currentUID == uid){
        Serial.println("Servir racao");
    }
    else{
        Serial.println("UDI invalido");
    }
}

// Button
void onInterrupBtn(){
    if(PROG_FUNC == DO_NOTHING) return;
    Serial.println("onInterrupBtn");
}

void onPressingBtn(int pressTime){
    if(pressTime == RFID_REG_TIME){
        if(PROG_FUNC == DO_NOTHING) enableRFIDRecordMode(true);
        else if(PROG_FUNC == RFID_REG) enableRFIDRecordMode(false);
        return;
    }
}

/* **************** ARDUINO CORE **************** */

void setup() {
    SPI.begin();
    Serial.begin(SERIAL_SPEED);

    MsTimer2::set(INTERRUP_TIME, onInterrupTime);
    MsTimer2::start();

    initRfidSensor(RFID_SDA, RFID_RST, onRFIDReceive);
    initPushButton(BTN_PIN, onInterrupBtn, onPressingBtn);
    initLedBehavior(LED);
}

void loop() {
    rfidListener();
    pushButtonListener();
    ledListener();
}

/* **************** UTIL **************** */

void enableRFIDRecordMode(bool enable){
    if(enable){
        PROG_FUNC = RFID_REG;
        setLedBehavior(LED_BLINKING);
        Serial.println("Modo de Registro de RFID");
    }
    else{
        PROG_FUNC = DO_NOTHING;
        setLedBehavior(LED_ALIGHT);
        Serial.println("Sair do modo de Registro de RFID");
    }
}
