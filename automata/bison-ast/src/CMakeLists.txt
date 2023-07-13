include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 9.1.0)
FetchContent_MakeAvailable(fmt)

find_package(BISON)
set(PARSER_DIR "${CMAKE_CURRENT_BINARY_DIR}/parser-out")
bison_target(parser parser.yy "${PARSER_DIR}/parser.cpp"
             DEFINES_FILE "${PARSER_DIR}/parser.h")

find_package(FLEX)
set(LEXER_DIR "${CMAKE_CURRENT_BINARY_DIR}/lexer-out")
flex_target(lexer lexer.ll "${LEXER_DIR}/lexer.cpp"
            DEFINES_FILE "${LEXER_DIR}/lexer.h")

add_executable(expr_parser expr_parser.cpp ast.cpp driver.cpp
                           ${BISON_parser_OUTPUTS})
target_include_directories(expr_parser PRIVATE "${PROJECT_SOURCE_DIR}/include"
                                               "${PARSER_DIR}" "${LEXER_DIR}")
target_link_libraries(expr_parser PRIVATE fmt::fmt)
