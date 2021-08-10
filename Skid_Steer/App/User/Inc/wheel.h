#ifndef WHEEL
#define WHEEL

#include "current_sensor.h"
#include "motor.h"
#include "encoder.h"

class Wheel{

    CurrentSensor _currentSensor;
    Motor _motor;
    float _radius;
    Encoder _encoder;

  public:

    Wheel(CurrentSensor& currentSensor, Motor& motor, Encoder& encoder);


};   


#endif