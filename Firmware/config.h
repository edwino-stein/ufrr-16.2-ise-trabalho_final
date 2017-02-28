#if !defined  _CONFIG
    #define _CONFIG

    #define SERIAL_SPEED 9600
    #define SERIAL_READ_BUFFER 64
    #define INTERRUP_TIME 500

    #define DO_NOTHING 0
    #define READY_TO_SERVE 1
    #define SERVING_FOOD 2
    #define RFID_REG 3
    #define RFID_CANCEL 4
    #define SERVE_FOOD_OVERRIDE 5
    #define SERVE_FOOD_FORCE 6

    #define RFID_REG_TIME 200
    #define RFID_COOLDOWN 1000
    #define DEFAULT_SERVE_FOOD_TIME 10000


    //Serial commands
    #define SERIAL_STATUS   's'
    #define SERIAL_OVERRIDE 'o'
    #define SERIAL_SET_TIME 't'
    #define SERIAL_REG_RFID 'r'
    #define SERIAL_SET_RFID 'u'

    //Food Measurer
    #define FM_ECHO 5
    #define FM_TRIG 4
    #define FOOD_SENSOR_MIN_DIS 3
    #define FOOD_SENSOR_MAX_DIS 30

    //Food Hatch
    #define FH_SERVO 6
    #define FH_SWITCH 7
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
    #define BTN_PRESS_MARGIN 50

    // LED
    #define LED 3
    #define LED_ALIGHT 0
    #define LED_OFF 1
    #define LED_BLINKING 2
    #define LED_BLINKING_TIMER 100
    #define LED_BLINK_DELAY 10

#endif
