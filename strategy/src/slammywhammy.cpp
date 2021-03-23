#include <strategy/slammywhammy.h>
#include <iostream>

SlammyWhammy::SlammyWhammy() {
    state_ = 0;
}

std::vector<int> SlammyWhammy::next_actionnext_action(SensorData input) {
    int output[] = {50, 100};
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}