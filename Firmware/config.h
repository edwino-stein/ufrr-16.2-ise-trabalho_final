#if !defined  _CONFIG
    #define _CONFIG

    #define SERIAL_SPEED 9600
    #define SERIAL_READ_BUFFER 64
    #define INTERRUP_TIME 500

    //Food Measurer
    #define FM_ECHO 5
    #define FM_TRIG 4
    #define FOOD_SENSOR_MIN_DIS 3
    #define FOOD_SENSOR_MAX_DIS 30

    //Food Hatch
    #define FH_SERVO 6
    #define FH_OPEN_TIME 1000
    #define FH_OPENING_SPEED 1
    #define FH_CLOSING_SPEED 3
    #define FOOD_HATCH_MIN_POS 10
    #define FOOD_HATCH_MAX_POS 39

    //RFID Sensor
    #define RFID_SDA 10
    #define RFID_SCK 13
    #define RFID_MOSI 11
    #define RFID_MISO 12
    #define RFID_NC -1      //Not used
    #define RFID_RST 9

    //Push Button
    #define BTN_PIN 2
    #define BTN_DELAY_ON_FALL 10

#endif
