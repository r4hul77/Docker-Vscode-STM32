#include "adc_device.h"

AdcDevice::AdcDevice(ADCParams& params):buffer(params.buffer), _m(params.m), _c(params.c), _val(0), idx(params.idx){
    init();
}

void AdcDevice::update(){
    _val =  _m*(float)buffer[idx] + _c;
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
}

float AdcDevice::sample(){
    return _val;
}