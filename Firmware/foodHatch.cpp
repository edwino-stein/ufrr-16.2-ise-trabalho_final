#include "config.h"
#include "foodHatch.h"
#include <Servo.h>
#include <Arduino.h>

Servo *servo;
bool isOpen;

void initFoodHatch(int servoPin){
    servo = new Servo();
    servo->attach(servoPin);
    isOpen = false;
    servo->write(FOOD_HATCH_MIN_POS);
    delay(15);
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

    isOpen = false;
}

void serveFood(int timer, int openSpeed, int closeSpeed){
    if(!isOpen) openFoodHatch(openSpeed);
    delay(timer);
    closeFoodHatch(closeSpeed);
}

bool isOpenFoodHatch(){
    return isOpen;
}
