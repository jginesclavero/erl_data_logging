cmake_minimum_required(VERSION 2.8.3)
project(erl_data_logging)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  geometry_msgs
  tf
)

catkin_package(
  #INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp
)

include_directories(
	include
  ${catkin_INCLUDE_DIRS}
)

add_executable(robot_pose_publisher src/robot_pose_publisher.cpp)
add_dependencies(robot_pose_publisher ${catkin_EXPORTED_TARGETS})
target_link_libraries(robot_pose_publisher ${catkin_LIBRARIES})

## Mark executables and/or libraries for installation
install(TARGETS
  robot_pose_publisher
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
