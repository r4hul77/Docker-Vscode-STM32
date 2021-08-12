#ifndef MOTOR
#define MOTOR

#include "tim.h"

class Motor
{

	public:
		enum channel
		{
			CHANNEL1 = 0,
			CHANNEL2,
			CHANNEL3,
			CHANNEL4
		};

	private:

		TIM_HandleTypeDef _pwmTimer;
		channel _channelNo;

		unsigned int _channel;

	public:


		Motor(TIM_HandleTypeDef& pwmTimer, Motor::channel& channelNo, unsigned int& channel);

		void run(float& voltagePercent);

		void init();

};

#endif