#ifndef MESSAGE_IN_H
#define MESSAGE_IN_H

#include <stdint.h>

struct message{
    enum Idx{
        CmdVel = 0,
        WheelConfig,
        RobotConfig,
        DiagReq
    } idx;

    uint8_t messageLen;

    message(Idx idx, uint8_t messageLen):idx(idx), messageLen(messageLen){

    }
};

struct wheel_config:public message{
    enum WheelIdx{
        WheelFL = 0,
        WheelFR,
        WheelBL,
        WheelBR
    } wheelIdx;
    enum config{
        SetPidGains = 0,
        CurrentSensorConfig,
        Radius,
        velFilter
    } configType;

    wheel_config(WheelIdx wheelIdx, config configType, uint8_t messageLen):message(message::Idx::WheelConfig, messageLen),
        wheelIdx(wheelIdx),
        configType(configType){
    }

};

struct pid_config:public wheel_config{
    float _kp;
    float _kd;
    float _ki;
    float _clamp;
    pid_config(wheel_config::WheelIdx wheelId, float kp, float kd, float ki, float clamp):
        wheel_config(wheelId,  wheel_config::config::SetPidGains, 20),
        _kp(kp), _kd(kd), _ki(ki), _clamp(clamp){

        }
};

struct current_sensor_config: public wheel_config{
    float m;
    float c;
    current_sensor_config(wheel_config::WheelIdx wheelId, float m, float c):
        wheel_config(wheelId, wheel_config::config::CurrentSensorConfig, 12),
        m(m), c(c){

        }
};

struct radius_config: public wheel_config{
    float radius;
    radius_config(wheel_config::WheelIdx wheelId, float radius):
    wheel_config(wheelId, wheel_config::config::Radius, 8),
    radius(radius){

    }
};

struct vel_filter_config: public wheel_config{
    uint8_t size;
    vel_filter_config(wheel_config::WheelIdx wheelIdx, uint8_t size):
    wheel_config(wheelIdx, wheel_config::config::velFilter, 5), size(size){

    }
};

struct robot_config: public message{
    enum ConfigIdx{
        VoltageConfig = 0,
        CurrentConfig,
        GeometryConfig
    } configIdx;

    robot_config(ConfigIdx configIdx, uint8_t messageLen): message(message::Idx::RobotConfig, messageLen),
     configIdx(configIdx){

    }
};

struct robot_voltage_config: public robot_config{
    float m;
    float c;

    robot_voltage_config(float m, float c): robot_config(robot_config::ConfigIdx::VoltageConfig, 12),
    m(m), c(c){

    }

};

struct robot_current_config: public robot_config{
    float m;
    float c;

    robot_current_config(float m, float c): robot_config(robot_config::ConfigIdx::CurrentConfig, 12),
    m(c), c(c){

    }
};

struct robot_geometry_config: public robot_config{
    float wheelBase;
    float trackWidth;

    robot_geometry_config(float wheelBase, float trackWidth): robot_config(robot_config::ConfigIdx::GeometryConfig, 12),
    wheelBase(wheelBase), trackWidth(trackWidth){

    }
};


#endif