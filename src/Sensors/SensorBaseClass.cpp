#include <Arduino.h>
#include "../../include/Sensors/SensorBaseClass.h"


class SensorBaseClass {
    
    private: 
        int _receivePin = 0; // underscore used to differentiate private from public variables
        int _transmitPin = 0;
        int _baudRate = 0;

    public:

        int getReceivePin() {
            return _receivePin;
        }

        int getTransmitPin() {
            return _transmitPin;
        }

        int getBaudRate() {
            return _baudRate;
        }

};