#ifndef ADC_DEVICE
#define ADC_DEVICE
#include "adc.h"
#include "utils.h"


struct ADCParams
{
	uint16_t* buffer;
	uint8_t idx;
	float m;
	float c;

	ADCParams(uint16_t* buffer, uint8_t idx, float m, float c):
		buffer(buffer), idx(idx), m(m), c(c)
	{

	}
};

class AdcDevice
{
		uint16_t* buffer;
		float _m;
		float _c; //converts y = mx +c, where x is adc reading and c is the bias and m is scale
		float _val;
		uint8_t idx;


	public:

		AdcDevice(ADCParams& params);

		void init();

		void update();

		float get_m();

		float get_c();

		void set_m(float m);

		void set_c(float c);

		void parseAndSetParams(char* buffer, int& pos, uint16_t bufferLen);

		float sample();
};

#endif