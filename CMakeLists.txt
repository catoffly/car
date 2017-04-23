cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0012 NEW)

project(car )
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/home/fa/matrix/lib/includes")
include_directories("/home/fa/matrix/lib")
link_directories(${OpenCV_LIB_DIR})
link_directories("/home/fa/matrix/lib/libfahw.a" "/home/fa/matrix/lib/libfahw.so")
aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}  ${OpenCV_LIBS} libfahw.a libfahw.so)

