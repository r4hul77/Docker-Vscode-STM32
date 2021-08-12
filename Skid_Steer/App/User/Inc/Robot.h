#ifndef ROBOT_H
#define ROBOT_H
#include "adc_device.h"
#include "wheel.h"
#include "PID.h"
#include "message_in.h"

struct RobotParams
{

	WheelParams wheelFLParams;
	WheelParams wheelFRParams;
	WheelParams wheelBLParams;
	WheelParams wheelBRParams;

	ADCParams voltageParams;

	ADCParams currentSensorParams;

	float refV;
	float refOmega;
	float wheelBase;
	float trackWidth;

	RobotParams(WheelParams wheelFLParams,
				WheelParams wheelFRParams,
				WheelParams wheelBLParams,
				WheelParams wheelBRParams,
				ADCParams voltageParams,
				ADCParams currentSensorParams,
				float refV,
				float refOmega,
				float wheelBase,
				float trackWidth): wheelFLParams(wheelFLParams), wheelFRParams(wheelFRParams),
		wheelBLParams(wheelBLParams), wheelBRParams(wheelBRParams),
		voltageParams(voltageParams), currentSensorParams(currentSensorParams),
		refV(refV), refOmega(refOmega), wheelBase(wheelBase), trackWidth(trackWidth)
	{

	}

};


class Robot
{

		Wheel wheelFL;
		Wheel wheelFR;
		Wheel wheelBL;
		Wheel wheelBR;
		AdcDevice batVolt;
		AdcDevice currentSensor;

		float refV;
		float refOmega;
		float wheelBase;
		float trackWidth;

	public:

		Robot(RobotParams&);

		void parseAndDecide(char* buffer, int& pos, uint16_t bufferLen);

		void run();

		void update();

		void setRefSpeeds();

};


#endif