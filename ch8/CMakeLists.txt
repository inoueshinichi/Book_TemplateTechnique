cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch8 ==========")

# # Header Files
# file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# message("Header Files: ${EXE_INCLUDES}")

# # Source Files
# file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# message("Source Files: ${EXE_SOURCES}")

add_executable(type_erasure_void_pointer
    main_type_erasure_void_pointer.cpp
    type_erasure_void_pointer.hpp
)

add_executable(type_erasure_virtual_table
    main_type_erasure_virtual_table.cpp
    type_erasure_virtual_table.hpp
)

add_executable(non_template_base_and_template_derived
    main_non_template_base_and_template_derived.cpp
    non_template_base_and_template_derived.hpp
)

add_executable(type_erasure_any
    main_type_erasure_any.cpp
    type_erasure_any.hpp
)

add_executable(type_erasure_functional
    main_type_erasure_functional.cpp
    type_erasure_functional.hpp
)