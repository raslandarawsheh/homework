cmake_minimum_required(VERSION 3.1)
# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
PROJECT (display)

find_package(OpenCV REQUIRED PATHS "/home/rasland/installation/OpenCV-master/lib/cmake/opencv4")
include_directories( ${OpenCV_INCLUDE_DIRS} )

#SET("OpenCV_LIBS" "/home/rasland/installation/OpenCV-master/lib/cmake/opencv4")

add_executable(display main.cpp )

target_link_libraries( display ${OpenCV_LIBS} )

