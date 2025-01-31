cmake_minimum_required(VERSION 3.19)

project(StridedPsum)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-O3>")
add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-march=native>")
add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-ffast-math>")

find_package(benchmark REQUIRED)
add_executable(driver driver.cc)
target_link_libraries(driver benchmark::benchmark)
