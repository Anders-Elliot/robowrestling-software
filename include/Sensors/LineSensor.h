#include <Arduino.h>
#include "SensorBaseClass.h"

class LineSensor: public SensorBaseClass {
    private:
        const int _lineSensorValue;
        const int _lineSensorReceivePin;
        const int _lineSensorThreshold;

    public:
        LineSensor();
        LineSensor(int sensorValue, int sensorPin, int sensorThreshold);
        ~LineSensor();

        int getReceivePin();
        int getTransmitPin();
        int getBaudRate();

        void debugPrintData();
        int getSensorValue();
        bool lineDetected(); 
};