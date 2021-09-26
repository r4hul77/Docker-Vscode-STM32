// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from simpl_msgs:msg/ADCConfig.idl
// generated code does not contain a copyright notice

#ifndef SIMPL_MSGS__MSG__DETAIL__ADC_CONFIG__STRUCT_H_
#define SIMPL_MSGS__MSG__DETAIL__ADC_CONFIG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/ADCConfig in the package simpl_msgs.
typedef struct simpl_msgs__msg__ADCConfig
{
  float m;
  float c;
} simpl_msgs__msg__ADCConfig;

// Struct for a sequence of simpl_msgs__msg__ADCConfig.
typedef struct simpl_msgs__msg__ADCConfig__Sequence
{
  simpl_msgs__msg__ADCConfig * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} simpl_msgs__msg__ADCConfig__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SIMPL_MSGS__MSG__DETAIL__ADC_CONFIG__STRUCT_H_
