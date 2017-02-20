#if !defined  _FOOD_MEASURER
    #define _FOOD_MEASURER

    #define FOOD_SENSOR_MIN_DIS 3
    #define FOOD_SENSOR_MAX_DIS 30
    const int FOOD_SENSOR_DIST_DELTA = FOOD_SENSOR_MAX_DIS - FOOD_SENSOR_MIN_DIS;

    void initFoodSensor(int trigger, int echo);
    float getFoodPercentage(int checkTimes);
    
#endif
