#ifndef basicrobot_h
#define basicrobot_h

#include <simulator/robot.h>

class BasicRobot: public Robot { //basic robot for testing purposes
	public: BasicRobot(double x, double y, double angle);
};

#endif