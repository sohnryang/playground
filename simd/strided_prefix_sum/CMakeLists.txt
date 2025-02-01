cmake_minimum_required(VERSION 3.19)

project(StridedPsum)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
FetchContent_Declare(
  google_benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.0
)
FetchContent_MakeAvailable(google_benchmark)
add_executable(bench bench.cc kernels.cc)
target_link_libraries(bench benchmark::benchmark)
target_compile_options(bench PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:-O3>" PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:-march=native>" PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:-ffast-math>")
set_property(TARGET bench PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
