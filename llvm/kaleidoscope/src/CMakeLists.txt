find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

find_package(Boost REQUIRED COMPONENTS program_options)

message(STATUS "Found Boost ${Boost_VERSION}")

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(fmt)

add_library(Lexer lexer.cpp)
target_include_directories(Lexer PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_library(Parser parser.cpp ast.cpp)
target_include_directories(Parser PUBLIC "${PROJECT_SOURCE_DIR}/include" PUBLIC "${LLVM_INCLUDE_DIRS}")
llvm_map_components_to_libnames(llvm_libs core)
target_link_libraries(Parser PUBLIC Lexer PUBLIC ${llvm_libs} PUBLIC fmt::fmt)

add_executable(kalc kalc.cpp)
target_include_directories(kalc PRIVATE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${Boost_INCLUDE_DIRS}")
target_link_libraries(kalc PRIVATE Parser PRIVATE ${Boost_LIBRARIES} PRIVATE ${llvm_libs})
