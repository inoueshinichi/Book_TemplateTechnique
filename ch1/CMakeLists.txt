cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch1 ==========")

# # Header Files
# file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# message("Header Files: ${EXE_INCLUDES}")

# # Source Files
# file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# message("Source Files: ${EXE_SOURCES}")

add_executable(smalltalk_container
    smalltalk.hpp
    main_smalltalk.cpp
)

add_executable(macro_max
    macro_max.hpp
    main_macro_max.cpp
)