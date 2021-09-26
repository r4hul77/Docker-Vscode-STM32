#ifndef MICRO_ROS_WARRPER_H
#define MICRO_ROS_WRAPPER_H

#include "Robot.h"
#include <usart.h>

//Hardware Stuff
#include <stm32f4xx_hal.h>

//MICRO ROS STUFF
#include <rmw_microxrcedds_c/config.h>
#include <ucdr/microcdr.h>
#include <uxr/client/client.h>
#include <rmw_microros/rmw_microros.h>
#include <rcl/rcl.h>
#include <rcl/init.h>
#include "../Microros/src/microros_transports/dma_transport.h"
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <string>
#include "microros_allocators.h"


//ROS STUFF
#include <simpl_msgs/msg/robot_msg.h>
#include <geometry_msgs/msg/twist.h>

#define PUB_DELAY 10

class SimplMicroRos
{

		Robot m_simpl;
		rcl_publisher_t m_robotMsgPublisher;
		simpl_msgs__msg__RobotMsg m_robotMsg;
		std::string m_nodeName;
		rcl_allocator_t m_allocator;
		rcl_node_t m_node;
		rclc_support_t m_support;
		rcl_subscription_t m_cmdVelSubscriber;
		static SimplMicroRos* sp_urosPointer;
		rcl_timer_t m_timer;
		geometry_msgs__msg__Twist m_cmdVelMsg;


	public:

		rclc_executor_t m_executor;


		SimplMicroRos(RobotParams& robotParams, std::string nodeName);

		void init();

		void publish();

		void controls_loop();

		static void cmd_vel_callback(const void* msgin);

		static void timer_callback(rcl_timer_t* timer, int64_t last_call_time);

		void convert_to_wheel_msg(simpl_msgs__msg__WheelMsg& urosMsg, WheelMsgOut& stmMsg);

		void convert_to_robot_msg(simpl_msgs__msg__RobotMsg& urosMsg, RobotMsgOut& stmMsg);


};


#endif