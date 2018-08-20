cmake_minimum_required(VERSION 2.8.3)
project(ros_hello)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
)


set(wiringPi_include "/user/local/include")

LINK_DIRECTORIES("/usr/local/lib")
add_message_files(
  FILES
  Message1.msg
  Message2.msg
)

generate_messages(
  DEPENDENCIES std_msgs
)


catkin_package(
 LIBRARIES ros_hello
 CATKIN_DEPENDS  roscpp std_msgs

)


include_directories(
  ${catkin_INCLUDE_DIRS}
  ${wiringPi_include}
)


#add_executable(pub_node src/pub_node.cpp)
#add_dependencies(pub_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(pub_node
#  ${catkin_LIBRARIES} wiringPi
#)


add_executable(sub_node src/sub_node.cpp)
add_dependencies(sub_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(sub_node
  ${catkin_LIBRARIES} wiringPi
)



