#include "current_sensor.h"

CurrentSensor::CurrentSensor(ADC_HandleTypeDef &adc, float m, float c):_adc(adc), _m(m), _c(c){
    init();
}

float CurrentSensor::update(){
    return _m*(float)HAL_ADC_GetValue(&_adc) + _c;
}

float CurrentSensor::get_m(){
    return _m;
}

float CurrentSensor::get_c(){
    return _c;
}

void CurrentSensor::set_m(float m){
    this->_m = m;
}

void CurrentSensor::set_c(float c){
    this->_c = c;
}

void CurrentSensor::init(){
    HAL_ADC_Start(&_adc);
}