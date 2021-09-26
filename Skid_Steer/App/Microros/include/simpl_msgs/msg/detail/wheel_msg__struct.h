// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from simpl_msgs:msg/WheelMsg.idl
// generated code does not contain a copyright notice

#ifndef SIMPL_MSGS__MSG__DETAIL__WHEEL_MSG__STRUCT_H_
#define SIMPL_MSGS__MSG__DETAIL__WHEEL_MSG__STRUCT_H_

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
  simpl_msgs__msg__WheelMsg__FL = 0
};

/// Constant 'FR'.
enum
{
  simpl_msgs__msg__WheelMsg__FR = 1
};

/// Constant 'BL'.
enum
{
  simpl_msgs__msg__WheelMsg__BL = 2
};

/// Constant 'BR'.
enum
{
  simpl_msgs__msg__WheelMsg__BR = 3
};

// Struct defined in msg/WheelMsg in the package simpl_msgs.
typedef struct simpl_msgs__msg__WheelMsg
{
  uint8_t wheel_idx;
  float angular_velocity;
  float current;
  int16_t ticks;
  float output_voltage;
} simpl_msgs__msg__WheelMsg;

// Struct for a sequence of simpl_msgs__msg__WheelMsg.
typedef struct simpl_msgs__msg__WheelMsg__Sequence
{
  simpl_msgs__msg__WheelMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} simpl_msgs__msg__WheelMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SIMPL_MSGS__MSG__DETAIL__WHEEL_MSG__STRUCT_H_
