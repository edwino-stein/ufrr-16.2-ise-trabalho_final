#include "pushButton.h"

int btnPin;
int btnCount;
void (*onFall)(int);

void initPushButton(int pin, void (*intCallback)(), void (*fallCallback)(int)){
    pinMode(pin, INPUT);
    attachInterrupt(pin - 2, intCallback, FALLING);
    onFall = fallCallback;
    btnPin = pin;
    btnCount = 0;
}

void pushButtonListener(){

    if(digitalRead(btnPin) == HIGH){
        onFall(++btnCount);
        delay(BTN_DELAY_ON_FALL);
        return;
    }

    btnCount = 0;
}
