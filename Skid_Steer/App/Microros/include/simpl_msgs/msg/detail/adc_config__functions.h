// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from simpl_msgs:msg/ADCConfig.idl
// generated code does not contain a copyright notice

#ifndef SIMPL_MSGS__MSG__DETAIL__ADC_CONFIG__FUNCTIONS_H_
#define SIMPL_MSGS__MSG__DETAIL__ADC_CONFIG__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "simpl_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "simpl_msgs/msg/detail/adc_config__struct.h"

/// Initialize msg/ADCConfig message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * simpl_msgs__msg__ADCConfig
 * )) before or use
 * simpl_msgs__msg__ADCConfig__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
bool
simpl_msgs__msg__ADCConfig__init(simpl_msgs__msg__ADCConfig * msg);

/// Finalize msg/ADCConfig message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__ADCConfig__fini(simpl_msgs__msg__ADCConfig * msg);

/// Create msg/ADCConfig message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * simpl_msgs__msg__ADCConfig__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
simpl_msgs__msg__ADCConfig *
simpl_msgs__msg__ADCConfig__create();

/// Destroy msg/ADCConfig message.
/**
 * It calls
 * simpl_msgs__msg__ADCConfig__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__ADCConfig__destroy(simpl_msgs__msg__ADCConfig * msg);


/// Initialize array of msg/ADCConfig messages.
/**
 * It allocates the memory for the number of elements and calls
 * simpl_msgs__msg__ADCConfig__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
bool
simpl_msgs__msg__ADCConfig__Sequence__init(simpl_msgs__msg__ADCConfig__Sequence * array, size_t size);

/// Finalize array of msg/ADCConfig messages.
/**
 * It calls
 * simpl_msgs__msg__ADCConfig__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__ADCConfig__Sequence__fini(simpl_msgs__msg__ADCConfig__Sequence * array);

/// Create array of msg/ADCConfig messages.
/**
 * It allocates the memory for the array and calls
 * simpl_msgs__msg__ADCConfig__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
simpl_msgs__msg__ADCConfig__Sequence *
simpl_msgs__msg__ADCConfig__Sequence__create(size_t size);

/// Destroy array of msg/ADCConfig messages.
/**
 * It calls
 * simpl_msgs__msg__ADCConfig__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__ADCConfig__Sequence__destroy(simpl_msgs__msg__ADCConfig__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SIMPL_MSGS__MSG__DETAIL__ADC_CONFIG__FUNCTIONS_H_
