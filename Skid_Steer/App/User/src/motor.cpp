#include "motor.h"

Motor::Motor(TIM_HandleTypeDef& pwmTimer, Motor::channel channelNo, unsigned int channel): _pwmTimer(pwmTimer), _channelNo(channelNo),  _channel(channel)
{
	init();
}

void Motor::init()
{
	HAL_TIM_Base_Start_IT(&_pwmTimer);
	float voltage = 0;
	run(voltage);
	//HAL_TIM_PWM_Start(&_pwmTimer, _channel);
}

void Motor::run(float& voltagePercent)
{
	uint32_t ticks = 1500 + voltagePercent * 500 - 1;

	switch (_channel)
	{
	case CHANNEL1:
		_pwmTimer.Instance->CCR1 = ticks;
		break;
	case CHANNEL2:
		_pwmTimer.Instance->CCR2 = ticks;
		break;
	case CHANNEL3:
		_pwmTimer.Instance->CCR3 = ticks;
		break;
	case CHANNEL4:
		_pwmTimer.Instance->CCR4 = ticks;
		break;
	default:
		break;
	}

	HAL_TIM_PWM_Start(&_pwmTimer, _channel);
}