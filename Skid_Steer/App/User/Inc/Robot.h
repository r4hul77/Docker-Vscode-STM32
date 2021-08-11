#ifndef ROBOT_H
#define ROBOT_H
#include "adc_device.h"
#include "wheel.h"
#include "PID.h"


struct RobotParams{
    
    WheelParams wheelFlParams;
    WheelParams wheelFRParams;
    WheelParams wheelBLParams;
    WheelParams wheelBRParams;
    
    ADC_HandleTypeDef voltageSensorHandle;
    float votlageSensorM;
    float voltageSensorC;
    
    ADC_HandleTypeDef currentSensorHandle;
    float currentSensorM;
    float currentSensorC;

    float refV;
    float refOmega;
    float wheelBase;
    float trackWidth;

};


class Robot{

    Wheel wheelFL;
    Wheel wheelFR;
    Wheel wheelBL;
    Wheel wheelBR;
    AdcDevice batVolt;
    AdcDevice currentSensor;
    
    float refV;
    float refOmega;
    float wheelbase;
    float trackWidth;

  public:
    
    Robot(RobotParams);

    void parseAndDecide(char* buffer, int& pos, uint16_t bufferLen);

    void run();

    void update();

};


#endif