#ifndef CURRENT_SENSOR
#define CURRENT_SENSOR
#include "adc.h"

class CurrentSensor{
    ADC_HandleTypeDef _adc;
    float _m;
    float _c; //converts y = mx +c, where x is adc reading and c is the bias and m is scale

  public:

    CurrentSensor(ADC_HandleTypeDef &adc, float m, float c);

    void init();

    float update();

    float get_m();

    float get_c();

    void set_m(float m);

    void set_c(float c);
};

#endif