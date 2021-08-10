#include "encoder.h"

Encoder::Encoder(TIM_HandleTypeDef& timer): _timer(timer){}

int16_t Encoder::update(){
    uint16_t ticks = (uint16_t)_timer.Instance->CNT;
    int16_t deltaTicks = ticks - _pticks;
    if(deltaTicks > 32768)
        overflow = PosOverFlow;
    else if(deltaTicks < -32768)
        overflow = NegOverFLow;
    else
        overflow = NoOverFlow;
    
    int16_t ret;
    switch (overflow)
    {
    case PosOverFlow:
        ret = deltaTicks - 0xffff;
        break;
    
    case NegOverFLow:
        ret = 0xffff - deltaTicks;
        break;

    default:
        ret = deltaTicks;
        break;
    }
    return ret;

}