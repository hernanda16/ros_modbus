cmake_minimum_required(VERSION 3.0.2)
project(comm_motor)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

include_directories(/usr/local/include/modbus)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} src/${PROJECT_NAME}.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} modbus)