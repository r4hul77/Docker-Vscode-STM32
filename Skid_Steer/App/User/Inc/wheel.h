#ifndef WHEEL
#define WHEEL

#include "PID.h"
#include "adc_device.h"
#include "motor.h"
#include "encoder.h"
#include "adc.h"
#include "utils.h"


struct WheelParams
{
	float radius;
	TIM_HandleTypeDef encoderTimer;
	TIM_HandleTypeDef pwmTimer;
	Motor::channel motorChannel;
	unsigned int motorChannelName;
	PID::PIDParams pidParams;
	//float dt; Commented for future use
	ADCParams adcParams;
	uint8_t filterSize;

	WheelParams(float radius,
				TIM_HandleTypeDef encoderTimer,
				TIM_HandleTypeDef pwmTimer,
				Motor::channel motorChannel,
				unsigned int motorChannelName,
				PID::PIDParams pidParams,
				//float dt, Commented for future use
				ADCParams& adcParams,
				uint8_t filterSize): radius(radius), encoderTimer(encoderTimer), pwmTimer(pwmTimer),
		motorChannel(motorChannel), motorChannelName(motorChannelName),
		pidParams(pidParams), adcParams(adcParams), filterSize(filterSize)
	{

	}


};
class Wheel
{

		AdcDevice _currentSensor;
		Motor _motor;
		float _radius;
		Encoder _encoder;
		PID _pidController;
		movingAvgFilter<float> _velFilter;
		uint32_t _pTicks;
		float _refVel;

	public:


		Wheel(WheelParams&);

		void update();

		void run(float bVoltage);

		void setRefVel(float refVel);

		void parseAndDecide(char* buffer, int& pos, uint16_t bufferLen);

};


#endif