#include "config.h"
#include "pushButton.h"

int btnPin;
int btnCount;
unsigned long int btnTimer = 0;
void (*onFall)(int);
void (*btnIntCallback)();

bool hasPresseted = false;
bool hasInterrupt = false;

void btnInterrupt(){
    if(hasPresseted && !hasInterrupt) btnIntCallback();
    hasInterrupt = true;
}

void initPushButton(int pin, void (*intCallback)(), void (*fallCallback)(int)){
    pinMode(pin, INPUT);
    attachInterrupt(pin - 2, btnInterrupt, FALLING);
    btnIntCallback = intCallback;
    onFall = fallCallback;
    btnPin = pin;
    btnCount = 0;
}

void pushButtonListener(){

    if(digitalRead(btnPin) == HIGH){

        btnCount++;
        if(btnCount > BTN_PRESS_MARGIN){
            onFall(btnCount);
            hasPresseted = true;
        }

        delay(BTN_DELAY_ON_FALL);
        return;
    }

    hasPresseted = false;
    hasInterrupt = false;
    btnCount = 0;
}

bool isPushButtonPresseted(){
    return digitalRead(btnPin) == HIGH;
}
