#ifndef MOTOR
#define MOTOR

#include "tim.h"

class Motor{

  public:
    enum channel{
      CHANNEL1=0,
      CHANNEL2
    };

  private:
    
    TIM_HandleTypeDef _pwmTimer;
    channel _channelNo;

    unsigned int _channel;

  public:


    Motor(TIM_HandleTypeDef& pwmTimer, Motor::channel& channelNo, unsigned int& channel);

    void run(float &voltagePercent);

    void init();

};

#endif