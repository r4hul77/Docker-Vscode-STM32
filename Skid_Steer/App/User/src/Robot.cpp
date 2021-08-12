#include "Robot.h"

Robot::Robot(RobotParams& params):
     wheelFL(params.wheelFLParams),
     wheelFR(params.wheelFRParams),
     wheelBL(params.wheelBLParams),
     wheelBR(params.wheelBRParams),
     batVolt(voltageSensorParams),
     currentSensor(currentSensorParams),
     refV(params.refV),
     refOmega(params.refOmega),
     wheelBase(params.wheelBase),
     trackWidth(params.trackWidth)
     {

}

void Robot::parseAndDecide(char* buffer, int& pos, uint16_t bufferLen){
    
    message::Idx msgType = (message::Idx)buffer[0];
    uint8_t msgLen = (uint8_t)buffer[1];
    int pos = 2;
    
    switch (msgType)
    {
        case message::Idx::CmdVel:
            parseFloat(buffer, pos, msgLen, refV);
            parseFloat(buffer, pos, msgLen, refOmega);
            setRefSpeeds();
        break;
    
        case message::Idx::WheelConfig:
            
            wheel_config::WheelIdx idx = (wheel_config::WheelIdx)buffer[++pos];
            
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
}

void Robot::update(){
    wheelFL.update();
    wheelFR.update();
    wheelBR.update();
    wheelBL.update();
    batVolt.update();
    currentSensor.update();
}

void Robot::run(){
    float voltage = batVolt.sample();
    wheelFL.run(voltage);
    wheelFR.run(voltage);
    wheelBR.run(voltage);
    wheelBL.run(voltage);
}

void Robot::setRefSpeeds(){
    //2*v = lv + rv
    //om*0.5*tw = (lv - rv)
    //lv = v + 0.25*tw*om
    //rv = v - 0.25*tw*om
    float factor = 0.25*trackWidth*refOmega;
    float leftSpeeds  = refV + factor;
    float rightSpeeds = refV - factor;
    wheelFL.setRefVel(leftSpeeds);
    wheelFR.setRefVel(rightSpeeds);
    wheelBL.setRefVel(leftSpeeds);
    wheelBR.setRefVel(rightSpeeds);
}