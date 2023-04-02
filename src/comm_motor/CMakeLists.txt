cmake_minimum_required(VERSION 3.0.2)
project(comm_motor)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES comm
 CATKIN_DEPENDS roscpp std_msgs
 DEPENDS system_lib
)

include_directories(
  include
  /usr/local/include/modbus
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} src/${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} modbus)
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


# add_executable(comm_motor src/comm_motor.cpp)
# target_link_libraries(comm_motor ${catkin_LIBRARIES} modbus)
# add_dependencies(${comm_motor} ${${comm_motor}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})