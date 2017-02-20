#if !defined  _FOOD_MEASURER
    #define _FOOD_MEASURER

    #if !defined _CONFIG
        #define FOOD_SENSOR_MIN_DIS 3
        #define FOOD_SENSOR_MAX_DIS 30
    #endif

    const int FOOD_SENSOR_DIST_DELTA = FOOD_SENSOR_MAX_DIS - FOOD_SENSOR_MIN_DIS;

    void initFoodSensor(int triggerPin, int echoPin);
    float getFoodPercentage(int checkTimes);

#endif
