#include "wheel.h"


Wheel::Wheel(WheelParams& params):
	_currentSensor(params.adcParams),
	_motor(params.pwmTimer, params.motorChannel, params.motorChannelName),
	_radius(params.radius),
	_encoder(params.encoderTimer),
	_pidController(params.pidParams),
	_velFilter(params.filterSize),
	_pTicks(0),
	_refVel(0)
{

}

void Wheel::update()
{
	int16_t val = _encoder.update();
	uint32_t ticks = HAL_GetTick();
	int16_t deltaTicks = (ticks - _pTicks);
	_ticks = deltaTicks;
	_pTicks = ticks;
	_velFilter.update(((float)deltaTicks * 1000.0 / PPR) / deltaTicks);

}

void Wheel::setRefVel(float refVel)
{
	_refVel = refVel / _radius;
}

void Wheel::run(float bVoltage)
{
	velNow = _velFilter.sample();
	output = _pidController.update(_refVel, velNow);
	float voltagePercent = output / bVoltage;
	_motor.run(voltagePercent);
}

WheelMsgOut Wheel::getWheelMsg(wheel_config::WheelIdx id)
{
	return WheelMsgOut(id, velNow, _currentSensor.sample(), _ticks, output);
}

void Wheel::parseAndDecide(char* buffer, int& pos, uint16_t bufferLen)
{
	wheel_config::config idx = (wheel_config::config)buffer[pos++];

	switch (idx)
	{
	case wheel_config::config::SetPidGains:
	{
		_pidController.parseAndSetParams(buffer, pos, bufferLen);

		break;
	}
	case wheel_config::config::CurrentSensorConfig:
	{
		_currentSensor.parseAndSetParams(buffer, pos, bufferLen);

		break;
	}
	case wheel_config::config::Radius:
	{
		parseFloat(buffer, pos, bufferLen, _radius);

		break;
	}
	default:
		break;
	}

}

