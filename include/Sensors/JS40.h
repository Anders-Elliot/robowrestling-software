#include <Arduino.h>

class JS40 {
    private:
        int _pin;

    public: 
        JS40(int receivePin, int baudRate);
        ~JS40();

        bool objectDetected(); 

};