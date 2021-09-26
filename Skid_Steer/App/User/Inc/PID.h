#ifndef PID_H
#define PID_H

#include "stm32f4xx_hal.h"
#include "utils.h"

class PID
{
		float _IError;
		float _pError;
		uint32_t _pt;

	public:

		struct PIDParams
		{

			float _kp;
			float _kd;
			float _ki;
			float _clamp;

			PIDParams(float kp, float kd, float ki, float clamp): _kp(kp), _kd(kd), _ki(ki), _clamp(clamp)
			{

			}

		} _params;


		PID(PIDParams params);

		float update(float ref, float state);

		void set_gains(float kp, float kd, float ki, float clamp);

};


#endif