// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from simpl_msgs:msg/RobotMsg.idl
// generated code does not contain a copyright notice

#ifndef SIMPL_MSGS__MSG__DETAIL__ROBOT_MSG__STRUCT_H_
#define SIMPL_MSGS__MSG__DETAIL__ROBOT_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'wheel_front_right'
// Member 'wheel_front_left'
// Member 'wheel_back_right'
// Member 'wheel_back_left'
#include "simpl_msgs/msg/detail/wheel_msg__struct.h"

// Struct defined in msg/RobotMsg in the package simpl_msgs.
typedef struct simpl_msgs__msg__RobotMsg
{
  uint32_t time;
  float battery_voltage;
  float battery_current;
  simpl_msgs__msg__WheelMsg wheel_front_right;
  simpl_msgs__msg__WheelMsg wheel_front_left;
  simpl_msgs__msg__WheelMsg wheel_back_right;
  simpl_msgs__msg__WheelMsg wheel_back_left;
} simpl_msgs__msg__RobotMsg;

// Struct for a sequence of simpl_msgs__msg__RobotMsg.
typedef struct simpl_msgs__msg__RobotMsg__Sequence
{
  simpl_msgs__msg__RobotMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} simpl_msgs__msg__RobotMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SIMPL_MSGS__MSG__DETAIL__ROBOT_MSG__STRUCT_H_
