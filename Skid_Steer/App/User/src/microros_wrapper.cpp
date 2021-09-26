#include "microros_wrapper.h"



SimplMicroRos::SimplMicroRos(RobotParams& robotParams, std::string nodeName): m_simpl(robotParams), m_nodeName(nodeName), m_allocator(rcutils_get_zero_initialized_allocator())
{
	m_allocator.allocate      = microros_allocate;
	m_allocator.deallocate    = microros_deallocate;
	m_allocator.reallocate    = microros_reallocate;
	m_allocator.zero_allocate =  microros_zero_allocate;
	sp_urosPointer = this;

}


void SimplMicroRos::init()
{
	rmw_uros_set_custom_transport(
		true,
		(void*) &huart3,
		dma_transport_open,
		dma_transport_close,
		dma_transport_write,
		dma_transport_read);

	rcutils_set_default_allocator(&m_allocator);
	rclc_support_init(&m_support, 0, NULL, &m_allocator);

	rclc_node_init_default(&m_node, m_nodeName.c_str(), "", &m_support);
	rclc_publisher_init_default(&m_robotMsgPublisher, &m_node, ROSIDL_GET_MSG_TYPE_SUPPORT(simpl_msgs, msg, RobotMsg), "SimplRobot");
	rclc_subscription_init_default(&m_cmdVelSubscriber, &m_node, ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist), "CmdVel");

	m_executor = rclc_executor_get_zero_initialized_executor();
	unsigned int num_handles = 1 + 1; //One for publisher One for Subscriber
	rclc_executor_init(&m_executor, &m_support.context, num_handles, &m_allocator);
	rclc_executor_add_subscription(&m_executor, &m_cmdVelSubscriber, &m_cmdVelMsg, &cmd_vel_callback, ON_NEW_DATA);
	rclc_timer_init_default(&m_timer, &m_support, RCL_MS_TO_NS(PUB_DELAY), timer_callback);
	rclc_executor_add_timer(&m_executor, &m_timer);

}

void SimplMicroRos::publish()
{
	RobotMsgOut msg = m_simpl.getInfo(HAL_GetTick());
	convert_to_robot_msg(m_robotMsg, msg);
	rcl_publish(&m_robotMsgPublisher, &m_robotMsg, NULL);
}

void SimplMicroRos::cmd_vel_callback(const void* msgin)
{
	const geometry_msgs__msg__Twist* msg = (const geometry_msgs__msg__Twist*)msgin;
	sp_urosPointer->m_simpl.setTargetVel(msg->linear.x, msg->angular.z);
	sp_urosPointer->m_robotMsg.battery_voltage = msg->linear.x;
}

void SimplMicroRos::timer_callback(rcl_timer_t* timer, int64_t last_call_timer)
{
	if (timer != NULL)
		sp_urosPointer->publish();
}

void SimplMicroRos::controls_loop()
{
	m_simpl.update();
	m_simpl.run();
}

void SimplMicroRos::convert_to_robot_msg(simpl_msgs__msg__RobotMsg& urosMsg, RobotMsgOut& msg)
{
	urosMsg.battery_current = msg.current;
	urosMsg.battery_voltage = msg.batVolt;
	urosMsg.time            = msg._time;
	convert_to_wheel_msg(urosMsg.wheel_back_left, msg.wheelBL);
	convert_to_wheel_msg(urosMsg.wheel_back_right, msg.wheelBR);
	convert_to_wheel_msg(urosMsg.wheel_front_left, msg.wheelFL);
	convert_to_wheel_msg(urosMsg.wheel_front_right, msg.wheelFR);

}

void SimplMicroRos::convert_to_wheel_msg(simpl_msgs__msg__WheelMsg& urosMsg, WheelMsgOut& msg)
{

	urosMsg.angular_velocity = msg.vel;
	urosMsg.current = msg.current;
	urosMsg.output_voltage = msg.output;
	urosMsg.ticks = msg.ticks;
}

SimplMicroRos* SimplMicroRos::sp_urosPointer = NULL;