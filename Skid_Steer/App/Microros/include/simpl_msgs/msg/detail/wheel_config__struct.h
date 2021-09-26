// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from simpl_msgs:msg/WheelConfig.idl
// generated code does not contain a copyright notice

#ifndef SIMPL_MSGS__MSG__DETAIL__WHEEL_CONFIG__STRUCT_H_
#define SIMPL_MSGS__MSG__DETAIL__WHEEL_CONFIG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'FL'.
enum
{
  simpl_msgs__msg__WheelConfig__FL = 0
};

/// Constant 'FR'.
enum
{
  simpl_msgs__msg__WheelConfig__FR = 1
};

/// Constant 'BL'.
enum
{
  simpl_msgs__msg__WheelConfig__BL = 2
};

/// Constant 'BR'.
enum
{
  simpl_msgs__msg__WheelConfig__BR = 3
};

/// Constant 'PIDGAINS'.
enum
{
  simpl_msgs__msg__WheelConfig__PIDGAINS = 0
};

/// Constant 'CURRENTSENSOR'.
enum
{
  simpl_msgs__msg__WheelConfig__CURRENTSENSOR = 1
};

/// Constant 'RADIUS'.
enum
{
  simpl_msgs__msg__WheelConfig__RADIUS = 2
};

/// Constant 'VELFILTER'.
enum
{
  simpl_msgs__msg__WheelConfig__VELFILTER = 3
};

// Include directives for member types
// Member 'pid_gains'
#include "simpl_msgs/msg/detail/pid_gains__struct.h"
// Member 'current_sensor_config'
#include "simpl_msgs/msg/detail/adc_config__struct.h"

// Struct defined in msg/WheelConfig in the package simpl_msgs.
typedef struct simpl_msgs__msg__WheelConfig
{
  uint8_t wheel_idx;
  uint8_t message_config;
  simpl_msgs__msg__PidGains pid_gains;
  simpl_msgs__msg__ADCConfig current_sensor_config;
  float radius;
  uint16_t vel_filter_size;
} simpl_msgs__msg__WheelConfig;

// Struct for a sequence of simpl_msgs__msg__WheelConfig.
typedef struct simpl_msgs__msg__WheelConfig__Sequence
{
  simpl_msgs__msg__WheelConfig * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} simpl_msgs__msg__WheelConfig__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SIMPL_MSGS__MSG__DETAIL__WHEEL_CONFIG__STRUCT_H_
