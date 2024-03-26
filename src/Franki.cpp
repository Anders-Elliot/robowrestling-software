#include <Arduino.h>
#include "../include/Franki.h"
#include "../include/Sensors/lineSensor.h"

class Franki {
    private:
        bool atBounds;
        LineSensor LineSensorLeft;
        LineSensor LineSensorRight;

    public:
        void sampleFloor() {

            int floorReading = 0;
            int sampleCount = 100;
        
            for (int i = 0; i < sampleCount; i++)
            {
                int leftValue = LineSensorLeft.getSensorValue();
                int rightValue = LineSensorRight.getSensorValue();

                Serial.print("Left Sensor Value: ");
                Serial.println(leftValue);
                Serial.print("Right Sensor Value: ");
                Serial.println(rightValue);

                int average = (leftValue + rightValue) / 2;
                Serial.print("Average: ");
                Serial.println(average);                

                floorReading += average;

                delay(100);
            }

            floorReading /= sampleCount;            
        }    
};