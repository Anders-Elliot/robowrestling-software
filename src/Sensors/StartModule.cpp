#include <Arduino.h>

class StartModule {
    private:
        int _pin;

    public: 
        StartModule(int pin) : _pin(pin) {
            pinMode(_pin, INPUT);
        }
        
        ~StartModule() {}

        bool isActive() {
            return digitalRead(_pin) == HIGH;
        }

        int getValue() {
            return analogRead(_pin);
        }
};
