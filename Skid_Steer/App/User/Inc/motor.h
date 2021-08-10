#ifndef MOTOR
#define MOTOR

#include "tim.h"

class Motor{

    TIM_HandleTypeDef _pwmTimer;
    enum channel{
      CHANNEL1=0,
      CHANNEL2
    } _channelNo;

    unsigned int _channel;

  public:

    Motor(TIM_HandleTypeDef& pwmTimer, Motor::channel channelNo, unsigned int channel);

    void run(float &voltagePercent);

    void init();

};

#endif