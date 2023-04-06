#ifndef GUCCI_H
#define GUCCI_H

#include "Robots/Robot.h"
#include <Arduino.h>
#include <memory>
#include "Sensors/TFMini/TFMini.h"
#include "Sensors/LineSensor.h"
#include "Sensors/StartModule.h"

constexpr int LINE_THRESHOLD = 200; 

class Gucci : public Robot {
private: 
        TFMini* rightDist;
        TFMini* frontDist;
        TFMini* frontDist2;
        TFMini* leftDist;

        LineSensor* lineSensor1;
        LineSensor* lineSensor2;
        std::unique_ptr<StartModule> startModule;  
         




public: 
    Gucci() {
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
        //_sensors.push_back(leftDist); 
        //_sensors.push_back(rightDist); 

    }

    void UpdateState() override {
        _state.lidars[0] = 0xFFFF; 
        _state.lidars[1] = 0xFFFF; 
        _state.lidars[2] = leftDist->GetDistance(); 
        _state.lidars[3] = rightDist->GetDistance(); 
        _state.lidars[4] = 0xFFFF;
        _state.lidars[5] = 0xFFFF;  

        Serial.printf("Left: %d, Right: %d \n", lineSensor1->GetDetection(), lineSensor2->GetDetection());
        _state.enabled = startModule->isActive(); 


        if (lineSensor1->GetDetection() < LINE_THRESHOLD || lineSensor2->GetDetection() < LINE_THRESHOLD) {
            _state.atBounds = true; 
        } else {
            _state.atBounds = false; 
        }
    } 


}; 

#endif 