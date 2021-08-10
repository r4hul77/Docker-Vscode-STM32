#include "wheel.h"


Wheel::Wheel(CurrentSensor& currentSensor, Motor& motor, Encoder& encoder):_currentSensor(currentSensor), _motor(motor), _encoder(encoder){};
