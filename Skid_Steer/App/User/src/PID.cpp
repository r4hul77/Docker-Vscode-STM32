#include "PID.h"

PID::PID(PID::PIDParams params): _IError(0), _pError(0), _pt(0), _params(params){

}

float PID::update(float ref, float state){
    float error = ref - state;
    uint32_t ticks =  HAL_GetTick();
    float dt = (float)(ticks - _pt)/1000;
    _IError = dt*error;
    _IError = (_IError < _params._clamp) ? 
             ((_IError > -_params._clamp ) ? _IError : -_params._clamp)
             : _params._clamp;
    _pt = ticks;
    _pError = error;
    return error*_params._kp + _params._kd*(error - _pError)/dt + 
                    _IError*_params._ki;

}

void PID::parseAndSetParams(char* buffer, int &pos, uint16_t bufferLen){
    parseFloat(buffer, pos, bufferLen, _params._kp);
    parseFloat(buffer, pos, bufferLen, _params._kd);
    parseFloat(buffer, pos, bufferLen, _params._ki);
    parseFloat(buffer, pos, bufferLen, _params._clamp);
}
