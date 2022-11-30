find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

find_package(Boost REQUIRED COMPONENTS program_options)

message(STATUS "Found Boost ${Boost_VERSION}")

add_library(Lexer lexer.cpp)
target_include_directories(Lexer PRIVATE "${PROJECT_SOURCE_DIR}/include")

add_library(Parser parser.cpp ast.cpp)
target_include_directories(Parser PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(Parser PRIVATE Lexer)

add_executable(kalc kalc.cpp)
target_include_directories(kalc PRIVATE "${PROJECT_SOURCE_DIR}/include" PRIVATE "${Boost_INCLUDE_DIRS}")
target_link_libraries(kalc PRIVATE Lexer PRIVATE ${Boost_LIBRARIES})
