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

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_executable(tests tests.cc kernels.cc)
target_link_libraries(tests GTest::gtest_main GTest::gmock_main)
target_compile_options(tests PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:-march=native>" PRIVATE)

include(GoogleTest)
gtest_discover_tests(tests)
