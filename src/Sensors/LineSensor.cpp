#include <Arduino.h>
#include "../include/Sensors/SensorBaseClass.h"

class LineSensor : public SensorBaseClass {
    private:
        const int _lineSensorValue;
        const int _lineSensorReceivePin;
        const int _lineSensorThreshold;

    public:

        LineSensor() : _lineSensorValue(0), _lineSensorReceivePin(0), _lineSensorThreshold(0){            
        }

        LineSensor(int sensorValue, int sensorPin, int sensorThreshold) : _lineSensorValue(sensorValue), _lineSensorReceivePin(sensorPin), _lineSensorThreshold(sensorThreshold) {
        }

        ~LineSensor() {
        }

        int getSensorValue() {
            return analogRead(_lineSensorReceivePin);
        }

        bool lineDetected() {
            return _lineSensorValue > _lineSensorThreshold;
        }

        void debugPrintData() {
            Serial.print("Line Sensor at pin: " + _lineSensorReceivePin);
            Serial.print("====================================");
            while (true)
            {
                Serial.println("Value is: " + _lineSensorValue);
            }
            
        }
};
