cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch5 ==========")

# # Header Files
# file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# message("Header Files: ${EXE_INCLUDES}")

# # Source Files
# file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# message("Source Files: ${EXE_SOURCES}")

add_executable(sfinae1
    main_sfinae1.cpp
    sfinae1.hpp
)