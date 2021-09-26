// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from simpl_msgs:msg/ADCConfig.idl
// generated code does not contain a copyright notice
#include "simpl_msgs/msg/detail/adc_config__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
simpl_msgs__msg__ADCConfig__init(simpl_msgs__msg__ADCConfig * msg)
{
  if (!msg) {
    return false;
  }
  // m
  // c
  return true;
}

void
simpl_msgs__msg__ADCConfig__fini(simpl_msgs__msg__ADCConfig * msg)
{
  if (!msg) {
    return;
  }
  // m
  // c
}

simpl_msgs__msg__ADCConfig *
simpl_msgs__msg__ADCConfig__create()
{
  simpl_msgs__msg__ADCConfig * msg = (simpl_msgs__msg__ADCConfig *)malloc(sizeof(simpl_msgs__msg__ADCConfig));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(simpl_msgs__msg__ADCConfig));
  bool success = simpl_msgs__msg__ADCConfig__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
simpl_msgs__msg__ADCConfig__destroy(simpl_msgs__msg__ADCConfig * msg)
{
  if (msg) {
    simpl_msgs__msg__ADCConfig__fini(msg);
  }
  free(msg);
}


bool
simpl_msgs__msg__ADCConfig__Sequence__init(simpl_msgs__msg__ADCConfig__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  simpl_msgs__msg__ADCConfig * data = NULL;
  if (size) {
    data = (simpl_msgs__msg__ADCConfig *)calloc(size, sizeof(simpl_msgs__msg__ADCConfig));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = simpl_msgs__msg__ADCConfig__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        simpl_msgs__msg__ADCConfig__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
simpl_msgs__msg__ADCConfig__Sequence__fini(simpl_msgs__msg__ADCConfig__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      simpl_msgs__msg__ADCConfig__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

simpl_msgs__msg__ADCConfig__Sequence *
simpl_msgs__msg__ADCConfig__Sequence__create(size_t size)
{
  simpl_msgs__msg__ADCConfig__Sequence * array = (simpl_msgs__msg__ADCConfig__Sequence *)malloc(sizeof(simpl_msgs__msg__ADCConfig__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = simpl_msgs__msg__ADCConfig__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
simpl_msgs__msg__ADCConfig__Sequence__destroy(simpl_msgs__msg__ADCConfig__Sequence * array)
{
  if (array) {
    simpl_msgs__msg__ADCConfig__Sequence__fini(array);
  }
  free(array);
}
