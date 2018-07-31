cmake_minimum_required(VERSION 2.6)
project(Sandpiles)

#Need OpenCV
find_package(OpenCV REQUIRED)

add_executable(Sandpiles Sandpiles.cpp)
target_link_libraries(Sandpiles ${OpenCV_LIBS})

