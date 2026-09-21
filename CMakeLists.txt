cmake_minimum_required(VERSION 3.16)
project(FirstProject CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)     #不允许自动降级
set(CMAKE_CXX_EXTENSIONS OFF)
add_library(reprojection src/reprojection.cpp)
target_include_directories(reprojection PUBLIC include)   #自动获得头文件路径

add_executable(test_reprojection tests/main.cpp)
target_link_libraries(test_reprojection PRIVATE reprojection)
