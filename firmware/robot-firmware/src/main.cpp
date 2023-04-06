#include <Arduino.h>
#include <SoftwareSerial.h>
#include <memory>

#include "MotorController/MotorController.h"
#include "Robots/Gucci/Gucci.h"
#include "TFMPlus.h"

#include "Strategies/SlammyWhammy/SlammyWhammy.h"
#include "Strategies/FigureEight/FigureEight.h"
#include "SabertoothSimplified.h"


// Init motor controller
// Make sure that everything is grounded
MotorController motorController{&Serial5};
SabertoothSimplified mc{Serial5};

Gucci gucci{};
TFMPlus tfm{};
RobotState currentState; 
SlammyWhammy<RobotState, RobotState> strategy(30, 100); 
FigureEight<RobotState, RobotState> figureEightStrategy(-100, 850); 
void setup() {
  Serial2.begin(115200);
  tfm.begin(&Serial2);
  Serial5.begin(9600); 
  pinMode(A22, OUTPUT);
  analogWrite(A22, 500); 
}


void loop() {
  //Serial.println("======= NEW LOOP AAAA =======");
  gucci.UpdateSensors(); 
  gucci.UpdateState(); 
  
  currentState = gucci.GetCurrentState(); 
  if (currentState.enabled == 1) {
    auto output = strategy.Run(currentState); 
    mc.motor(1, output.currentRightMotorPow);
    mc.motor(2, -output.currentLeftMotorPow);  
  } else { 
    mc.stop(); 
  }


  delay(50);

}

/* emergency roomba strat */
// if (state.atBounds) {
//       state.backupUntilMillis = millis() + 1000;
//       state.isBackingUp = true;
//     }

//     if (state.isBackingUp) {
//       if (millis() >= state.backupUntilMillis) {
//         state.isBackingUp = false;
//       }

//       mc.motor(1, -30);
//       mc.motor(2, -30);
//     } else {
//       mc.motor(1, 100);
//       mc.motor(2, 100);
//     }
// }