#ifndef MESSAGE_OUT_H
#define MESSAGE_OUT_H

#include <stdint.h>
#include "message_in.h"
#include "utils.h"

struct WheelMsgOut
{
	wheel_config::WheelIdx idx;
	float vel;
	float current;
	int16_t ticks;
	float output;

	WheelMsgOut(wheel_config::WheelIdx id, float&  velNow, float current, int16_t& ticks, float& output):
		idx(id), vel(velNow), current(current), ticks(ticks), output(output)
	{

	}


	void convertToBytes(char* buffer, uint16_t bufferLen, int& pos)
	{
		std::memcpy(buffer + pos, (char* ) (uint8_t* ) &idx, 1);
		pos ++;
		float2Bytes(buffer, bufferLen, pos);
		float2Bytes(buffer, bufferLen, pos);
		std::memcpy(buffer + pos, (char* ) &ticks,  2);
		pos += 2;
		float2Bytes(buffer, bufferLen, pos);

	}
};

struct ADCMsgOut
{
	float _out;
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

	RobotMsgOut(uint32_t time, float batVolt, float current, WheelMsgOut wheelFR, WheelMsgOut wheelFL, WheelMsgOut wheelBL, WheelMsgOut wheelBR):
		_time(time), batVolt(batVolt), current(current), wheelFR(wheelFR), wheelFL(wheelFL), wheelBR(wheelBR), wheelBL(wheelBL)
	{

	}

	void convertToBytes(char* buffer, uint16_t bufferLen, int& pos)
	{
		uint322Bytes(buffer, _time, pos);
		float2Bytes(buffer, batVolt, pos);
		float2Bytes(buffer, current, pos);
		wheelFR.convertToBytes(buffer, bufferLen, pos);
		wheelFL.convertToBytes(buffer, bufferLen, pos);
		wheelBR.convertToBytes(buffer, bufferLen, pos);
		wheelBL.convertToBytes(buffer, bufferLen, pos);
	}

};

#endif