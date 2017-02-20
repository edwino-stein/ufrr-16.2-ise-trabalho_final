#include "foodMeasurer.h"
#include <Ultrasonic.h>

Ultrasonic *ultrasonic;

void initFoodSensor(int trigger, int echo){
    ultrasonic = new Ultrasonic(trigger, echo);
}

float getFoodPercentage(int checkTimes){

    long microsec;
    float distCm, amount = 0;
    int counter = checkTimes;

    for(int i = 0; i < checkTimes; i++){

        microsec = ultrasonic->timing();
        distCm = ultrasonic->convert(microsec, Ultrasonic::CM) - FOOD_SENSOR_MIN_DIS;
        delay(15);

        if(distCm > FOOD_SENSOR_DIST_DELTA){
            counter--;
            continue;
        }

        amount += distCm;
    }

    if(counter <= 0) amount = FOOD_SENSOR_DIST_DELTA;
    else amount /= counter;

    amount = 100 - (100*amount/FOOD_SENSOR_DIST_DELTA);
    return amount < 100 ? amount : 100;
}
