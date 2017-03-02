#include "config.h"
#include "foodHatch.h"
#include <Servo.h>
#include <Arduino.h>

Servo *servo;
bool isOpen;
int switchP;
int lastPos = 0;

void initFoodHatch(int servoPin, int switchPin){
    pinMode(switchPin, OUTPUT);
    switchP = switchPin;
    setEnabledFoodHatch(true);

    servo = new Servo();
    servo->attach(servoPin);
    isOpen = false;
    servo->write(FOOD_HATCH_MIN_POS);
    delay(30);
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
    delay(20);
    openFoodHatch(openSpeed);
    delay(timer);
    closeFoodHatch(closeSpeed);
    setEnabledFoodHatch(false);
}

bool isOpenFoodHatch(){
    return isOpen;
}

void setEnabledFoodHatch(bool enable){
  
    if(enable){
      servo->write(enable);
    }
    else{
      lastPos = servo->read();
    }

    digitalWrite(switchP, enable ? HIGH : LOW);
}
