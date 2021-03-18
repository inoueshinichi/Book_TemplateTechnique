cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch9 ==========")

# # Header Files
# file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# message("Header Files: ${EXE_INCLUDES}")

# # Source Files
# file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# message("Source Files: ${EXE_SOURCES}")

add_executable(basic_crtp
    main_basic_crtp.cpp
    basic_crtp.hpp
)

add_executable(barton_nackman_trick
    main_barton_nackman_trick.cpp
    barton_nackman_trick.hpp
)

add_executable(enable_shared_from_this
    main_enable_shared_from_this.cpp
    enable_shared_from_this.hpp
)