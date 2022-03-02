#include <strategy/kevin_brody_enemy.h>
#include <iostream>

KevinBrodyStrategyEnemy::KevinBrodyStrategyEnemy() {
    state = IDLE;
}

// remember to use IMU sensor somehow
std::vector<int> KevinBrodyStrategyEnemy::next_action(SensorData input) {
    int output[] = {0, 0};
    state = update_state(input);
    switch (state) {
    case FORWARD:
        output[0] = 100;
        output[1] = 100;
        break;
    case BACK:
        output[0] = -100;
        output[1] = -100;
        break;
    // fast af turn
    case TURN_LEFT:
        output[0] = 0;
        output[1] = 100;
        break;
    case TURN_RIGHT:
        output[0] = 100;
        output[1] = 0;
        break;
    case LEFT_BACK:
        output[0] = -50;
        output[1] = -100;
        break;
    case RIGHT_BACK:
        output[0] = -100;
        output[1] = -50;
        break;
    case STOP:
        output[0] = 0;
        output[1] = 0;
        break;
    // turns in place
    case SEARCH:
        output[0] = 25;
        output[1] = -25;
        break;
    default:
        break;
    }

    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

KevinBrodyStrategyEnemy::State KevinBrodyStrategyEnemy::update_state(SensorData input) {
    // TODO: implement, you can delete the stuff below
    // input.dist_buffer_[2] and 3 are the front ones
    // 0 and 1 are left
    // 4 and 5 are right
    // units are in centimeters
    // 1.5 meter
    // front left front right for the line sensors [0] [1]
    // left to right

    /* 
    LINE SENSORS
    both sensors = back
    left sensor = right back
    right sensor = left back
    
    DISTANCE SENSORS
    Both front sensors = forward
    Left front sensor
    Both left sensors(close) = forward
    Both left sensors(far) = turn left
    Both right sensors(close) = forward
    Both right sensors(far) = turn left
    Mid left and left right sensors(close) = left forward
    Mid left and left right sensors(far) = turn left
    Mid right and right sensors(close) = right forward
    Mid right and right sensors(far) = turn right
    */
    std::cout << "( " << input.dist_buffer_[0] << ", " << input.dist_buffer_[1] << ", " 
    << input.dist_buffer_[2] << ", " << input.dist_buffer_[3] << ", " 
    << input.dist_buffer_[4] <<", " << input.dist_buffer_[5] << " )\n";
   if(input.line_buffer_[0] > 150 && input.line_buffer_[1] > 150) {
       return BACK;
   }
   else if(input.line_buffer_[0] > 150) {
       return RIGHT_BACK;
   }
   else if(input.line_buffer_[1] > 150) {
       return LEFT_BACK;
   }
   else if(input.dist_buffer_[2] < 150 && input.dist_buffer_[3] < 150) {
       return FORWARD;
   }
   else if(input.dist_buffer_[0] < 100 && input.dist_buffer_[1] < 100) {
       return TURN_LEFT;
   }
   else if(input.dist_buffer_[4] < 100 && input.dist_buffer_[5] < 100) {
       return TURN_RIGHT;
   }
    else{ 
        return STOP;
    }
}

