cmake_minimum_required(VERSION 3.5)
project(hector_gazebo_plugins VERSION 0.5.3)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # we dont use add_compile_options with pedantic in message packages
  # because the Python C extensions dont comply with it
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-inconsistent-missing-override")
endif()


if(WIN32)
  add_compile_definitions(
    # For math constants
    _USE_MATH_DEFINES
    # Minimize Windows namespace collision
    NOMINMAX
    WIN32_LEAN_AND_MEAN
  )
endif()

find_package(ament_cmake REQUIRED)
#find_package(gazebo_dev REQUIRED)
#find_package(gazebo_msgs REQUIRED)
#find_package(gazebo_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(rosidl_default_generators REQUIRED)

link_directories(${gazebo_dev_LIBRARY_DIRS})


## Find gazebo
option(ENABLE_PROFILER "Enable Ignition Profiler" FALSE)
if(ENABLE_PROFILER)
  find_package(ignition-common3 QUIET COMPONENTS profiler)
  if(ignition-common3_FOUND)
    add_definitions("-DIGN_PROFILER_ENABLE=1" "-DIGN_PROFILER_REMOTERY=1")
    message(STATUS "Profiler is active")
  else()
    message(WARNING "Can't find Ignition common3. Profiler will not be actived")
    add_definitions("-DIGN_PROFILER_ENABLE=0" "-DIGN_PROFILER_REMOTERY=0")
  endif()
endif()

## Find Boost
#find_package(Boost REQUIRED COMPONENTS thread)
#include_directories(${Boost_INCLUDE_DIRS})

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/SetBias.srv"
 )


###########
## Build ##
###########

#add_library(hector_gazebo_reset_plugin SHARED
#  src/reset_plugin.cpp
#  )
#target_link_libraries(hector_gazebo_reset_plugin PUBLIC ${GAZEBO_LIBRARIES} include)
#ament_target_dependencies(gazebo_ros_joint_state_publisher
#  "gazebo_dev"
#  "gazebo_ros"
#  "rclcpp"
#  "sensor_msgs"
#)


#add_library(hector_gazebo_ros_imu src/gazebo_ros_imu.cpp)
#target_link_libraries(hector_gazebo_ros_imu ${Boost_LIBRARIES} ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})
#add_dependencies(hector_gazebo_ros_imu ${PROJECT_NAME}_generate_messages_cpp ${PROJECT_NAME}_gencfg)

#add_library(hector_gazebo_ros_magnetic src/gazebo_ros_magnetic.cpp)
#target_link_libraries(hector_gazebo_ros_magnetic ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})
#add_dependencies(hector_gazebo_ros_magnetic ${PROJECT_NAME}_gencfg)

#add_library(hector_gazebo_ros_gps src/gazebo_ros_gps.cpp)
#target_link_libraries(hector_gazebo_ros_gps ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})
#add_dependencies(hector_gazebo_ros_gps ${PROJECT_NAME}_gencfg)

#add_library(hector_gazebo_ros_sonar src/gazebo_ros_sonar.cpp)
#target_link_libraries(hector_gazebo_ros_sonar ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})
#add_dependencies(hector_gazebo_ros_sonar ${PROJECT_NAME}_gencfg)

#add_library(hector_servo_plugin src/servo_plugin.cpp)
#target_link_libraries(hector_servo_plugin ${Boost_LIBRARIES} ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES})

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html


#ament_export_libraries(gazebo_ros_projector)
#if(ENABLE_PROFILER)
#  target_include_directories(gazebo_ros_projector PUBLIC ${ignition-common3_INCLUDE_DIRS})
#  target_link_libraries(gazebo_ros_projector ${ignition-common3_LIBRARIES})
#endif()

# gazebo_ros_wheel_slip
#if(NOT GAZEBO_VERSION VERSION_LESS 9.5)
#  add_library(gazebo_ros_wheel_slip SHARED
#    src/gazebo_ros_wheel_slip.cpp
#  )
#  ament_target_dependencies(gazebo_ros_wheel_slip
#    "gazebo_dev"
#    "gazebo_ros"
#    "rclcpp"
#    "std_msgs"
#  )
#  target_link_libraries(gazebo_ros_wheel_slip
#    WheelSlipPlugin
#  )
#  target_include_directories(gazebo_ros_wheel_slip PUBLIC include)
#  ament_export_libraries(gazebo_ros_wheel_slip)
#endif()
#
#ament_export_include_directories(include)
#ament_export_dependencies(rclcpp)
#ament_export_dependencies(gazebo_dev)
#ament_export_dependencies(gazebo_msgs)
#ament_export_dependencies(gazebo_ros)
#
#if(BUILD_TESTING)
#  add_subdirectory(test)
#  find_package(ament_lint_auto REQUIRED)
#  ament_lint_auto_find_test_dependencies()
#endif()
#
#if(NOT WIN32)
#  if(NOT APPLE)
#    set(
#      AMENT_CMAKE_ENVIRONMENT_HOOKS_DESC_gazebo_plugins
#      "prepend-non-duplicate;LD_LIBRARY_PATH;${GAZEBO_PLUGIN_PATH}")
#  else()
#    set(
#      AMENT_CMAKE_ENVIRONMENT_HOOKS_DESC_gazebo_plugins
#      "prepend-non-duplicate;DYLD_LIBRARY_PATH;${GAZEBO_PLUGIN_PATH}")
#  endif()
#endif()
#ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/env-hooks/gazebo_plugins.sh.in")

ament_package()

#install(DIRECTORY include/
#        DESTINATION include)
#
#install(TARGETS
#    hector_gazebo_ros_gps
#    hector_gazebo_reset_plugin
#    hector_gazebo_ros_imu
#    hector_gazebo_ros_magnetic
#    hector_gazebo_ros_sonar
#  ARCHIVE DESTINATION lib
#  LIBRARY DESTINATION lib
#  RUNTIME DESTINATION bin)
#
#if(NOT GAZEBO_VERSION VERSION_LESS 9.5)
#install(TARGETS
#    gazebo_ros_wheel_slip
#  ARCHIVE DESTINATION lib
#  LIBRARY DESTINATION lib
#  RUNTIME DESTINATION bin)
#endif()
#
#install(DIRECTORY
#  worlds
#  DESTINATION share/${PROJECT_NAME}/
#)
#
#
#
#
#install(DIRECTORY
#  worlds
#  DESTINATION share/${PROJECT_NAME}/
#)
