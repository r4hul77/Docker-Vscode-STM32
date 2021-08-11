#ifndef ADC_DEVICE
#define ADC_DEVICE
#include "adc.h"
#include "utils.h"


class AdcDevice{
    ADC_HandleTypeDef _adc;
    float _m;
    float _c; //converts y = mx +c, where x is adc reading and c is the bias and m is scale
    float _val;


  public:

    AdcDevice(ADC_HandleTypeDef &adc, float& m, float& c);

    void init();

    void update();

    float get_m();

    float get_c();

    void parseAndSetParams(char* buffer, int &pos, uint16_t bufferLen);

    float sample();
  };

#endif