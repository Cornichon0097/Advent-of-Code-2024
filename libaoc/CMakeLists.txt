add_library(libaoc util.c)
target_link_libraries(libaoc PUBLIC compiler_flags)
target_include_directories(libaoc PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
