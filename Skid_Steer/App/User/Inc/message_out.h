#ifndef MESSAGE_OUT_H
#define MESSAGE_OUT_H

#include <stdint.h>
#include "utils.h"

struct WheelMsgOut
{
	float vel;
	float current;
	int16_t ticks;
	float output;

	WheelMsgOut(float&  velNow, float current, int16_t& ticks, float& output):
		vel(velNow), current(current), ticks(ticks), output(output)
	{

	}
};

struct RobotMsgOut
{
	uint32_t _time;
	float batVolt;
	float current;
	WheelMsgOut wheelFR;
	WheelMsgOut wheelFL;
	WheelMsgOut wheelBR;
	WheelMsgOut wheelBL;

	RobotMsgOut(uint32_t time, float batVolt, float current, WheelMsgOut wheelFR, WheelMsgOut wheelFL, WheelMsgOut wheelBR, WheelMsgOut wheelBL):
		_time(time), batVolt(batVolt), current(current), wheelFR(wheelFR), wheelFL(wheelFL), wheelBR(wheelBR), wheelBL(wheelBL)
	{

	}
};

#endif