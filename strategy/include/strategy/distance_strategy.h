#ifndef DISTANCE_STRATEGY_H
#define DISTANCE_STRATEGY_H
#include <strategy/strategy.h>

class DistanceStrat: public Strategy {
    public:
        DistanceStrat();
        std::vector<int> next_action(SensorData input);
        
        enum State {
            IDLE,
            APPROACH,
            TURN_RIGHT,
            TURN_LEFT
        };

        State state;
};
#endif