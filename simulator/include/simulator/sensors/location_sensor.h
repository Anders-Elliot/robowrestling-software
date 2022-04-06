#ifndef location_sensor_h
#define location_sensor_h

#include <simulator/sensors/abstract_location_sensor.h>

class LocactionSensor : public AbstractLocaitonSensor {
    public:
        LocactionSensor(std::shared_ptr<Robot> robot);
        double read();
        double getX();
        double getY();
};

#endif