// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from simpl_msgs:msg/PidGains.idl
// generated code does not contain a copyright notice

#ifndef SIMPL_MSGS__MSG__DETAIL__PID_GAINS__FUNCTIONS_H_
#define SIMPL_MSGS__MSG__DETAIL__PID_GAINS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "simpl_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "simpl_msgs/msg/detail/pid_gains__struct.h"

/// Initialize msg/PidGains message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * simpl_msgs__msg__PidGains
 * )) before or use
 * simpl_msgs__msg__PidGains__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
bool
simpl_msgs__msg__PidGains__init(simpl_msgs__msg__PidGains * msg);

/// Finalize msg/PidGains message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__PidGains__fini(simpl_msgs__msg__PidGains * msg);

/// Create msg/PidGains message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * simpl_msgs__msg__PidGains__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
simpl_msgs__msg__PidGains *
simpl_msgs__msg__PidGains__create();

/// Destroy msg/PidGains message.
/**
 * It calls
 * simpl_msgs__msg__PidGains__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__PidGains__destroy(simpl_msgs__msg__PidGains * msg);


/// Initialize array of msg/PidGains messages.
/**
 * It allocates the memory for the number of elements and calls
 * simpl_msgs__msg__PidGains__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
bool
simpl_msgs__msg__PidGains__Sequence__init(simpl_msgs__msg__PidGains__Sequence * array, size_t size);

/// Finalize array of msg/PidGains messages.
/**
 * It calls
 * simpl_msgs__msg__PidGains__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__PidGains__Sequence__fini(simpl_msgs__msg__PidGains__Sequence * array);

/// Create array of msg/PidGains messages.
/**
 * It allocates the memory for the array and calls
 * simpl_msgs__msg__PidGains__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
simpl_msgs__msg__PidGains__Sequence *
simpl_msgs__msg__PidGains__Sequence__create(size_t size);

/// Destroy array of msg/PidGains messages.
/**
 * It calls
 * simpl_msgs__msg__PidGains__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_simpl_msgs
void
simpl_msgs__msg__PidGains__Sequence__destroy(simpl_msgs__msg__PidGains__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SIMPL_MSGS__MSG__DETAIL__PID_GAINS__FUNCTIONS_H_
