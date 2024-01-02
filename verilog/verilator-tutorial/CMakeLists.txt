cmake_minimum_required(VERSION 3.19)
project(verilator-tutorial)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(verilator)
add_executable(Vtop tb.cc)
verilate(Vtop SOURCES top.v)
