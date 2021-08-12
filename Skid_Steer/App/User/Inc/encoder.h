#ifndef ENCODER
#define ENCODER

#include "tim.h"

class Encoder
{

		enum OverFlow
		{
			NoOverFlow,
			NegOverFLow,
			PosOverFlow,
		} overflow;
		uint32_t _pticks;
		TIM_HandleTypeDef _timer;

	public:

		Encoder(TIM_HandleTypeDef& timer);

		int16_t update();

		uint16_t sample();

};
#endif