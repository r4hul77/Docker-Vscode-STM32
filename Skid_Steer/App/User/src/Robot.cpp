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

void Robot::setTargetVel(float spV, float spOmega)
{
	refV = spV;
	refOmega = spOmega;
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
	setWheelTargetSpeeds();
	wheelFL.run(voltage);
	wheelFR.run(voltage);
	wheelBR.run(voltage);
	wheelBL.run(voltage);
}

void Robot::setWheelTargetSpeeds()
{
	/*
	v : velocity,
	om : angular velocity
	co-ordinate axis: x forward and z upwards
	lv : velocity of left wheel
	rv : velocity of right wheel
	tw : track width
	2*v = lv + rv
	om*0.5*tw = (lv - rv)
	lv = v + 0.25*tw*om
	rv = v - 0.25*tw*om */
	float factor = 0.25 * trackWidth * refOmega;
	float leftSpeeds  = refV + factor;
	float rightSpeeds = refV - factor;
	wheelFL.setTargetVel(leftSpeeds);
	wheelFR.setTargetVel(rightSpeeds);
	wheelBL.setTargetVel(leftSpeeds);
	wheelBR.setTargetVel(rightSpeeds);
}

RobotMsgOut Robot::getInfo(uint32_t ticks)
{
	WheelMsgOut wheelMSGFR = wheelFR.getWheelMsg();
	WheelMsgOut wheelMSGFL = wheelFL.getWheelMsg();
	WheelMsgOut wheelMSGBR = wheelBR.getWheelMsg();
	WheelMsgOut wheelMSGBL = wheelBL.getWheelMsg();
	RobotMsgOut ret(ticks, batVolt.sample(), currentSensor.sample(), wheelMSGFR, wheelMSGFL, wheelMSGBR, wheelMSGBL);
	return ret;
}