#include "config.h"
#include <SPI.h>
#include <MsTimer2.h>

void onInterrupTime(){
    Serial.println("onInterrupTime");
}

void setup() {
    SPI.begin();
    Serial.begin(SERIAL_SPEED);

    MsTimer2::set(INTERRUP_TIME, onInterrupTime);
    MsTimer2::start();
}

void loop() {
}
