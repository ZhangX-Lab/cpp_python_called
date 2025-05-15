cmake_minimum_required(VERSION 3.14)
project(pybind11_cpp_call_python)

set(CMAKE_CXX_STANDARD 17)

find_package(pybind11 REQUIRED) # 需要已安装 pybind11

add_executable(main main.cpp)

target_link_libraries(main PRIVATE pybind11::embed)