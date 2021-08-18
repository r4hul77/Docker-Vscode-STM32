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
		std::memcpy(buffer + pos, (char* )&idx, 4);
		pos += 4 ;
		float2Bytes(buffer, bufferLen, pos, bufferLen);
		float2Bytes(buffer, bufferLen, pos, bufferLen);
		std::memcpy(buffer + pos, (char* ) &ticks,  2);
		pos += 2;
		float2Bytes(buffer, bufferLen, pos, bufferLen);

	}

	static WheelMsgOut BytesToMessage(char* buffer, uint16_t bufferLen, int& pos){
		int id = 0;
		parseInt32(buffer, pos, bufferLen, id);
		float vel = 0;
		parseFloat(buffer, pos, bufferLen, vel);
		float current = 0;
		parseFloat(buffer, pos, bufferLen, current);
		int16_t ticks = 0;
		parseInt16(buffer, pos, bufferLen, ticks);
		float output = 0;
		parseFloat(buffer, pos, bufferLen, output);
		return WheelMsgOut(static_cast<wheel_config::WheelIdx>(id), vel, current, ticks, output);
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

	RobotMsgOut(uint32_t time, float batVolt, float current, WheelMsgOut wheelFR, WheelMsgOut wheelFL, WheelMsgOut wheelBR, WheelMsgOut wheelBL):
		_time(time), batVolt(batVolt), current(current), wheelFR(wheelFR), wheelFL(wheelFL), wheelBR(wheelBR), wheelBL(wheelBL)
	{

	}

	void convertToBytes(char* buffer, uint16_t bufferLen, int& pos)
	{
		uint322Bytes(buffer, _time, pos, bufferLen);
		float2Bytes(buffer, batVolt, pos, bufferLen);
		float2Bytes(buffer, current, pos, bufferLen);
		wheelFR.convertToBytes(buffer, bufferLen, pos);
		wheelFL.convertToBytes(buffer, bufferLen, pos);
		wheelBR.convertToBytes(buffer, bufferLen, pos);
		wheelBL.convertToBytes(buffer, bufferLen, pos);
	}

	static RobotMsgOut BytesToMessage(char* buffer, uint16_t bufferLen){
			uint32_t _retTime;
			int pos = 0;
			parseUint32(buffer, pos, bufferLen, _retTime);
			float retBatVolt;
			parseFloat(buffer, pos, bufferLen, retBatVolt);
			float retCurrent;
			parseFloat(buffer, pos, bufferLen, retCurrent);
			WheelMsgOut retWheelFR = WheelMsgOut::BytesToMessage(buffer, bufferLen, pos);
			WheelMsgOut retWheelFL = WheelMsgOut::BytesToMessage(buffer, bufferLen, pos);
			WheelMsgOut retWheelBR = WheelMsgOut::BytesToMessage(buffer, bufferLen, pos);
			WheelMsgOut retWheelBL = WheelMsgOut::BytesToMessage(buffer, bufferLen, pos);

			return RobotMsgOut(_retTime, retBatVolt, retCurrent, retWheelFR, retWheelFL, retWheelBR, retWheelBL);
	}

};

#endif