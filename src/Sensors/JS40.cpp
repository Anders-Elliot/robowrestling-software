#include <Arduino.h>

class JS40 {
    private:
        int _receivePin;
        int baudRate;

    public: 
        JS40(int receivePin, int baudRate) : _receivePin(receivePin), baudRate(baudRate){
            Serial.begin(baudRate);
            pinMode(_receivePin, INPUT);
        }
        
        ~JS40() {}

        bool objectDetected() {
            return digitalRead(_receivePin) == HIGH;
        }

};