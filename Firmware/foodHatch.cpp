#include "config.h"
#include "foodHatch.h"
#include <Servo.h>
#include <Arduino.h>

Servo *servo;
bool isOpen;
int switchP;

void initFoodHatch(int servoPin, int switchPin){
    pinMode(switchPin, OUTPUT);
    switchP = switchPin;
    setEnabledFoodHatch(true);

    servo = new Servo();
    servo->attach(servoPin);
    isOpen = false;
    servo->write(FOOD_HATCH_MIN_POS);
    delay(15);
    setEnabledFoodHatch(false);
}

void openFoodHatch(int speed){

    if(speed <= 0){
        servo->write(FOOD_HATCH_MAX_POS);
        isOpen = true;
        return;
    }

    for(int i = FOOD_HATCH_MIN_POS; i <= FOOD_HATCH_MAX_POS; i += speed){
        servo->write(i);
        delay(15);
    }

    if(servo->read() != FOOD_HATCH_MAX_POS){
        servo->write(FOOD_HATCH_MAX_POS);
        delay(15);
    }

    isOpen = true;
}

void closeFoodHatch(int speed){

    if(speed <= 0){
        servo->write(FOOD_HATCH_MIN_POS);
        isOpen = false;
        return;
    }

    for(int i = FOOD_HATCH_MAX_POS; i >= FOOD_HATCH_MIN_POS; i -= speed){
        servo->write(i);
        delay(15);
    }

    if(servo->read() != FOOD_HATCH_MIN_POS){
        servo->write(FOOD_HATCH_MIN_POS);
        delay(15);
    }

    isOpen = false;
}

void serveFood(int timer, int openSpeed, int closeSpeed){
    setEnabledFoodHatch(true);
    if(!isOpen) openFoodHatch(openSpeed);
    delay(timer);
    closeFoodHatch(closeSpeed);
    delay(60);
    setEnabledFoodHatch(false);
}

bool isOpenFoodHatch(){
    return isOpen;
}

void setEnabledFoodHatch(bool enable){
    digitalWrite(switchP, enable ? HIGH : LOW);
}
