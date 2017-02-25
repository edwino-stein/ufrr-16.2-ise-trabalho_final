#include "ledBehavior.h"

int ledPin;
int ledMode;
int ledBlinkTimer;
bool ledUpdateMode;

void initLedBehavior(int pin){
    pinMode(pin, OUTPUT);
    ledPin = pin;
    ledMode = 0;
    ledBlinkTimer = 0;
    ledUpdateMode = true;
}

void ledListener(){

    switch (ledMode) {
        case LED_ALIGHT:
            if(ledUpdateMode) digitalWrite(ledPin, HIGH);
        break;

        case LED_BLINKING:
            if(ledUpdateMode){
                digitalWrite(ledPin, !digitalRead(ledPin));
                ledBlinkTimer = 0;
            }
            else{
                ledBlinkTimer++;

                if(ledBlinkTimer >=  LED_BLINKING_TIMER){
                    ledUpdateMode = true;
                    ledBlinkTimer = 0;
                    return;
                }

                delay(LED_BLINK_DELAY);
            }
        break;

        case LED_OFF:
        default:
            if(ledUpdateMode) digitalWrite(ledPin, LOW);
    }

    ledUpdateMode = false;
}

void setLedBehavior(int mode){
    ledMode = mode;
    ledUpdateMode = true;
}
