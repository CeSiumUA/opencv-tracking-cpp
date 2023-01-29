cmake_minimum_required(VERSION 3.18)
project(opencv_tracking_cpp)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(opencv_tracking_cpp
        main.cpp)

target_link_libraries( opencv_tracking_cpp ${OpenCV_LIBS} )