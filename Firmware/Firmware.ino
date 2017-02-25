#include "config.h"
#include <SPI.h>
#include <MsTimer2.h>

#include "rfidController.h"
#include "pushButton.h"
#include "ledBehavior.h"

/* **************** FUNCTION DECLARATIONS **************** */

/**
 * TODO: Passar para um arquivo .h
 */
void enableRFIDRecordMode(bool enable);
void enableServerFoodMode(bool enable);

/* **************** GLOABAL VARS **************** */

char PROG_FUNC = READY_TO_SERVE;
String currentUID;
unsigned long int serveFoodTime = DEFAULT_SERVE_FOOD_TIME;
unsigned long int serveFoodClock = 0;
int rfidRestClock = 0;

/* **************** CALLBACKS **************** */

// Time
void onInterrupTime(){

    if(PROG_FUNC != READY_TO_SERVE){
        if(serveFoodClock >= serveFoodTime){
            if(PROG_FUNC == DO_NOTHING){
                enableServerFoodMode(true);
                Serial.println("pronto para servir");
                return;
            }
        }

        serveFoodClock += INTERRUP_TIME;
    }

    // Da um tempo na leitura RFID
    if(rfidRestClock <= 0){
        rfidRestClock = RFID_COOLDOWN;
        disableRfidReader(false);
    }
    else{
        disableRfidReader(true);
        rfidRestClock -= INTERRUP_TIME;
    }
}

// RFID
void onRFIDReceive(String uid){

    if(PROG_FUNC == RFID_REG){
        currentUID = uid;

        rfidRestClock = RFID_COOLDOWN*2;
        disableRfidReader(true);

        Serial.print("UID registrada: ");
        Serial.println(uid);
        enableRFIDRecordMode(false);
        return;
    }

    if(PROG_FUNC == READY_TO_SERVE){
        if(currentUID == uid){
            Serial.println("Servir racao");
            enableServerFoodMode(false);
        }
        else{
            Serial.println("UDI invalido");
        }
    }
}

// Button
void onInterrupBtn(){
    if(PROG_FUNC == DO_NOTHING) return;
    Serial.println("onInterrupBtn");
}

void onPressingBtn(int pressTime){
    if(pressTime == RFID_REG_TIME){

        if(PROG_FUNC == DO_NOTHING || PROG_FUNC == READY_TO_SERVE){
            enableRFIDRecordMode(true);
        }
        else if(PROG_FUNC == RFID_REG){
            enableRFIDRecordMode(false);
        }
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
    setLedBehavior(LED_ALIGHT);
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
    else if(PROG_FUNC == RFID_REG){
        PROG_FUNC = DO_NOTHING;
        setLedBehavior(LED_OFF);
        Serial.println("Sair do modo de Registro de RFID");
    }
}

void enableServerFoodMode(bool enable){
    if(enable){
        PROG_FUNC = READY_TO_SERVE;
        serveFoodClock = 0;
        setLedBehavior(LED_ALIGHT);
    }
    else if(PROG_FUNC == READY_TO_SERVE){
        PROG_FUNC = DO_NOTHING;
        setLedBehavior(LED_OFF);
        serveFoodClock = 0;
    }
}
