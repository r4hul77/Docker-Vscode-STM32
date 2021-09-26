// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from simpl_msgs:msg/WheelMsg.idl
// generated code does not contain a copyright notice

#ifndef SIMPL_MSGS__MSG__DETAIL__WHEEL_MSG__FUNCTIONS_H_
#define SIMPL_MSGS__MSG__DETAIL__WHEEL_MSG__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "simpl_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "simpl_msgs/msg/detail/wheel_msg__struct.h"

/// Initialize msg/WheelMsg message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * simpl_msgs__msg__WheelMsg
 * )) before or use
 * simpl_msgs__msg__WheelMsg__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
bool
simpl_msgs__msg__WheelMsg__init(simpl_msgs__msg__WheelMsg * msg);

/// Finalize msg/WheelMsg message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__WheelMsg__fini(simpl_msgs__msg__WheelMsg * msg);

/// Create msg/WheelMsg message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * simpl_msgs__msg__WheelMsg__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
simpl_msgs__msg__WheelMsg *
simpl_msgs__msg__WheelMsg__create();

/// Destroy msg/WheelMsg message.
/**
 * It calls
 * simpl_msgs__msg__WheelMsg__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__WheelMsg__destroy(simpl_msgs__msg__WheelMsg * msg);


/// Initialize array of msg/WheelMsg messages.
/**
 * It allocates the memory for the number of elements and calls
 * simpl_msgs__msg__WheelMsg__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
bool
simpl_msgs__msg__WheelMsg__Sequence__init(simpl_msgs__msg__WheelMsg__Sequence * array, size_t size);

/// Finalize array of msg/WheelMsg messages.
/**
 * It calls
 * simpl_msgs__msg__WheelMsg__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__WheelMsg__Sequence__fini(simpl_msgs__msg__WheelMsg__Sequence * array);

/// Create array of msg/WheelMsg messages.
/**
 * It allocates the memory for the array and calls
 * simpl_msgs__msg__WheelMsg__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
simpl_msgs__msg__WheelMsg__Sequence *
simpl_msgs__msg__WheelMsg__Sequence__create(size_t size);

/// Destroy array of msg/WheelMsg messages.
/**
 * It calls
 * simpl_msgs__msg__WheelMsg__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__WheelMsg__Sequence__destroy(simpl_msgs__msg__WheelMsg__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SIMPL_MSGS__MSG__DETAIL__WHEEL_MSG__FUNCTIONS_H_
