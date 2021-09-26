// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from simpl_msgs:msg/RobotConfig.idl
// generated code does not contain a copyright notice

#ifndef SIMPL_MSGS__MSG__DETAIL__ROBOT_CONFIG__STRUCT_H_
#define SIMPL_MSGS__MSG__DETAIL__ROBOT_CONFIG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'VOLTAGECONFIG'.
enum
{
  simpl_msgs__msg__RobotConfig__VOLTAGECONFIG = 0
};

/// Constant 'CURRENTCONFIG'.
enum
{
  simpl_msgs__msg__RobotConfig__CURRENTCONFIG = 1
};

/// Constant 'GEOMETRYCONFIG'.
enum
{
  simpl_msgs__msg__RobotConfig__GEOMETRYCONFIG = 2
};

// Include directives for member types
// Member 'voltage_sensor_config'
// Member 'current_sensor_config'
#include "simpl_msgs/msg/detail/adc_config__struct.h"

// Struct defined in msg/RobotConfig in the package simpl_msgs.
typedef struct simpl_msgs__msg__RobotConfig
{
  uint8_t message_config;
  simpl_msgs__msg__ADCConfig voltage_sensor_config;
  simpl_msgs__msg__ADCConfig current_sensor_config;
  float wheel_base;
  float track_width;
} simpl_msgs__msg__RobotConfig;

// Struct for a sequence of simpl_msgs__msg__RobotConfig.
typedef struct simpl_msgs__msg__RobotConfig__Sequence
{
  simpl_msgs__msg__RobotConfig * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} simpl_msgs__msg__RobotConfig__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SIMPL_MSGS__MSG__DETAIL__ROBOT_CONFIG__STRUCT_H_
