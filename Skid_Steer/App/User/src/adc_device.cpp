#include "adc_device.h"

AdcDevice::AdcDevice(ADC_HandleTypeDef &adc, float& m, float& c):_adc(adc), _m(m), _c(c), _val(0){
    init();
}

void AdcDevice::update(){
    _val =  _m*(float)HAL_ADC_GetValue(&_adc) + _c;
}

float AdcDevice::get_m(){
    return _m;
}

float AdcDevice::get_c(){
    return _c;
}

void AdcDevice::parseAndSetParams(char* buffer, int& pos, uint16_t bufferLen){
    parseFloat(buffer, pos, bufferLen, _m);
    parseFloat(buffer, pos, bufferLen, _c);
}

void AdcDevice::init(){
    HAL_ADC_Start(&_adc);
}

float AdcDevice::sample(){
    return _val;
}