#include "config.h"
#include <MsTimer2.h>

void onInterrupTime(){
    Serial.println("onInterrupTime");
}

void setup() {
    Serial.begin(SERIAL_SPEED);

    MsTimer2::set(INTERRUP_TIME, onInterrupTime);
    MsTimer2::start();

}

void loop() {
}
