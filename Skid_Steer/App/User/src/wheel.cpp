#include "wheel.h"


Wheel::Wheel(WheelParams& params):
    _currentSensor(params.adcHandle, params.m, params.c),
    _motor(params.pwmTimer, params.motorChannel, params.motorChannelName),
    _radius(params.radius),
    _encoder(params.encoderTimer),
    _pidController(params.pidParams),
    _velFilter(params.filterSize),
    _pTicks(0),
    _refVel(0){

    }

void Wheel::update(){
    int16_t val = _encoder.update();
    uint32_t ticks = HAL_GetTick();
    int16_t deltaTicks = (ticks - _pTicks);
    _velFilter.update(((float)val*1000)/deltaTicks);

}

void Wheel::setRefVel(float refVel){
    _refVel = refVel/_radius;
}

void Wheel::run(float bVoltage){
    float velNow = _velFilter.sample();
    float voltagePercent = _pidController.update(_refVel, velNow)/ bVoltage;
    _motor.run(voltagePercent);
}
