#include "Robot.h"

Robot::Robot(RobotParams& params):
	wheelFL(params.wheelFLParams),
	wheelFR(params.wheelFRParams),
	wheelBL(params.wheelBLParams),
	wheelBR(params.wheelBRParams),
	batVolt(params.voltageParams),
	currentSensor(params.currentSensorParams),
	refV(params.refV),
	refOmega(params.refOmega),
	wheelBase(params.wheelBase),
	trackWidth(params.trackWidth)
{

}

void Robot::parseAndDecide(char* buffer, int& pos, uint16_t bufferLen)
{

	message::Idx msgType = (message::Idx)buffer[pos++];
	uint8_t msgLen = (uint8_t)buffer[pos++];

	switch (msgType)
	{
	case message::Idx::CmdVel:
	{
		parseFloat(buffer, pos, msgLen, refV);
		parseFloat(buffer, pos, msgLen, refOmega);
		setRefSpeeds();
		break;
	}
	case message::Idx::RobotConfig:
	{
		robot_config::ConfigIdx idx = (robot_config::ConfigIdx)buffer[pos++];

		switch (idx)
		{
		case robot_config::ConfigIdx::VoltageConfig:
		{
			batVolt.parseAndSetParams(buffer, pos, bufferLen);
			break;
		}
		case robot_config::ConfigIdx::CurrentConfig:
		{
			currentSensor.parseAndSetParams(buffer, pos, bufferLen);
			break;
		}
		case robot_config::ConfigIdx::GeometryConfig:
		{
			parseFloat(buffer, pos, bufferLen, trackWidth);
			parseFloat(buffer, pos, bufferLen, wheelBase);
			break;
		}
		default:
			break;
		}
		break;
	}
	case message::Idx::WheelConfig:
	{
		wheel_config::WheelIdx idx = (wheel_config::WheelIdx)buffer[pos++];

		switch (idx)
		{
		case wheel_config::WheelIdx::WheelFL:
			wheelFL.parseAndDecide(buffer, pos, msgLen);
			break;

		case wheel_config::WheelIdx::WheelFR:
			wheelFR.parseAndDecide(buffer, pos, msgLen);
			break;

		case wheel_config::WheelIdx::WheelBR:
			wheelBR.parseAndDecide(buffer, pos, msgLen);
			break;

		default:
			wheelBL.parseAndDecide(buffer, pos, msgLen);
			break;
		}

		break;
	}
	default:

		break;

	}
}

void Robot::update()
{
	wheelFL.update();
	wheelFR.update();
	wheelBR.update();
	wheelBL.update();
	batVolt.update();
	currentSensor.update();
}

void Robot::run()
{
	float voltage = batVolt.sample();
	wheelFL.run(voltage);
	wheelFR.run(voltage);
	wheelBR.run(voltage);
	wheelBL.run(voltage);
}

void Robot::setRefSpeeds()
{
	//v is velocity, om is angular velocity with x forward and z upwards
	//lv is velocity of left wheel and rv is velocity of right wheel
	//tw is track width
	//2*v = lv + rv
	//om*0.5*tw = (lv - rv)
	//lv = v + 0.25*tw*om
	//rv = v - 0.25*tw*om
	float factor = 0.25 * trackWidth * refOmega;
	float leftSpeeds  = refV + factor;
	float rightSpeeds = refV - factor;
	wheelFL.setRefVel(leftSpeeds);
	wheelFR.setRefVel(rightSpeeds);
	wheelBL.setRefVel(leftSpeeds);
	wheelBR.setRefVel(rightSpeeds);
}

RobotMsgOut Robot::getInfo(uint32_t ticks)
{
	WheelMsgOut wheelMSGFR = wheelFR.getWheelMsg(wheel_config::WheelIdx::WheelFR);
	WheelMsgOut wheelMSGFL = wheelFL.getWheelMsg(wheel_config::WheelIdx::WheelFL);
	WheelMsgOut wheelMSGBR = wheelBR.getWheelMsg(wheel_config::WheelIdx::WheelBR);
	WheelMsgOut wheelMSGBL = wheelBL.getWheelMsg(wheel_config::WheelIdx::WheelBL);
	RobotMsgOut ret(ticks, batVolt.sample(), currentSensor.sample(), wheelMSGFR, wheelMSGFL, wheelMSGBR, wheelMSGBL);
	return ret;
}