cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(Advent-of-Code-2024
        VERSION 0.1.0
        DESCRIPTION "Calendar of small programming puzzles"
        LANGUAGES C)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE c_std_90)

set(gcc_like_c "$<COMPILE_LANG_AND_ID:C,GNU>")
target_compile_options(compiler_flags INTERFACE
    "$<${gcc_like_c}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wwrite-strings;-Wstrict-prototypes;-Wunreachable-code;-Werror;-g>>"
)

add_executable(day1.out day1/day1.c)
target_link_libraries(day1.out PUBLIC compiler_flags)

add_executable(day2.out day2/day2.c)
target_link_libraries(day2.out PUBLIC compiler_flags)
