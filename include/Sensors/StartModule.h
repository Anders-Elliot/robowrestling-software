#include <Arduino.h>

#ifndef START_MODULE_H
#define START_MODULE_H

class StartModule {
    private:
        int _pin;

    public: 
        StartModule(int pin);
        ~StartModule();

        bool isActive();
        int getValue(); 

};
#endif