#ifndef FROSTI_H
#define FROST_H

#include "Robot.h"
#include <Arduino.h>
#include <memory>
#include "sensors/TFMini/TFMini.h"
#include "sensors/LineSensor.h"
#include "sensors/StartModule.h"

constexpr int LINE_THRESHOLD = 300; 

class Frosti : public Robot {

private: 
        TFMini* rightDist;
        TFMini* frontDist;
        TFMini* frontDist2;
        TFMini* leftDist;

        LineSensor* lineSensor1;
        LineSensor* lineSensor2;
        std::unique_ptr<StartModule> startModule;  

        int floorReading = 0; 
        int samples = 0; 

public: 
    Frosti() {
        //TODO: replace these with the actual pin values
        
        Serial1.begin(115200); 
        Serial2.begin(115200);  
        Serial3.begin(115200); 
        Serial4.begin(115200); 

        startModule = std::make_unique<StartModule>(14);
        leftDist = new TFMini(&Serial3);
        rightDist =  new TFMini(&Serial2); 
        lineSensor1 = new LineSensor(A9);
        lineSensor2 = new LineSensor(A16);
        _sensors.push_back(lineSensor1); 
        _sensors.push_back(lineSensor2);
        _sensors.push_back(leftDist); 
        _sensors.push_back(rightDist); 
    }

    void updateState() override {
        _state.distanceToEnemy.setX(leftDist->GetDistance()); 
        _state.distanceToEnemy.setY(rightDist->GetDistance()); 
        //Serial.printf("Left: %d, Right: %d \n", leftDist->GetDistance(),rightDist->GetDistance());
        //Serial.printf("Left: %d, Right: %d \n", lineSensor1->GetDetection(),lineSensor2->GetDetection());
        _state.enabled = startModule->isActive(); 
        if (abs(lineSensor1->GetDetection() - floorReading) > LINE_THRESHOLD || abs(lineSensor2->GetDetection() - floorReading) > LINE_THRESHOLD) {
            _state.atBounds = true; 
        } else {
            _state.atBounds = false; 
        }
    }

    void sampleFloor() {
        unsigned int timestamp = millis(); 
        while (millis() - timestamp < 5000) {
            lineSensor1->Poll(); 
            lineSensor2->Poll(); 
            int leftFloor = lineSensor1->GetDetection(); 
            int rightFloor = lineSensor2->GetDetection(); 
            int avg = (leftFloor + rightFloor) / 2; 
            floorReading += avg; 
            samples++; 
        }
        floorReading = (floorReading / samples); 
    } 

}; 

#endif 