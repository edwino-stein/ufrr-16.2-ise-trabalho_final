#if !defined  _FOODHATCH
    #define _FOODHATCH

    #if !defined _CONFIG
        #define FOOD_HATCH_MIN_POS 5
        #define FOOD_HATCH_MAX_POS 40
    #endif

    void initFoodHatch(int servoPin, int switchPin);
    void openFoodHatch(int speed);
    void closeFoodHatch(int speed);
    void serveFood(int timer, int openSpeed, int closeSpeed);
    bool isOpenFoodHatch();
    void setEnabledFoodHatch(bool enable);

#endif
