#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <string>
#include <functional>
#include "rcl_interfaces/msg/set_parameters_result.hpp"

using namespace std::chrono_literals;

class ParametersClass: public rclcpp::Node
{
  public:
    ParametersClass()
      : Node("parameter_node")
    {
      this->declare_parameter<std::string>("Test.my_string", "world");
      this->declare_parameter<std::string>("Test.my_string1", "TestWorld");
      parameter_string_ = this->get_parameter("Test.my_string").as_string();
      callback_handler = this->add_on_set_parameters_callback(std::bind(&ParametersClass::parametersCallback, this, std::placeholders::_1));
      timer_ = this->create_wall_timer(
      1000ms, std::bind(&ParametersClass::respond, this));
    }
    void respond()
    {
      RCLCPP_INFO(this->get_logger(), "Hello %s", parameter_string_.c_str());
    }

    rcl_interfaces::msg::SetParametersResult parametersCallback(
        const std::vector<rclcpp::Parameter> &parameters)
    {
        rcl_interfaces::msg::SetParametersResult result;
        result.successful = true;
        result.reason = "success";
        RCLCPP_WARN(this->get_logger(), "CALL BACK TRIGGERED");
        for (const auto &parameter : parameters)
        {
            if (parameter.get_name() == "Test.my_string" &&
                parameter.get_type() == rclcpp::ParameterType::PARAMETER_STRING)
            {
                parameter_string_ = parameter.as_string();
                RCLCPP_INFO(this->get_logger(), "Parameter 'my_string' changed: %s", parameter_string_.c_str());
            }
        }
        return result;
    }
  private:
    std::string parameter_string_;
    rclcpp::TimerBase::SharedPtr timer_;
    OnSetParametersCallbackHandle::SharedPtr callback_handler;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ParametersClass>());
  rclcpp::shutdown();
  return 0;
}