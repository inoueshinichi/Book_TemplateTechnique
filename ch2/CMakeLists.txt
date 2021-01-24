cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch2 ==========")

# # Header Files
# file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# message("Header Files: ${EXE_INCLUDES}")

# # Source Files
# file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# message("Source Files: ${EXE_SOURCES}")

add_executable(main_stack
    main_stack.cpp
    template_stack.hpp
    template_stack.cpp
)

add_executable(main_pointer_params
    main_pointer_params.cpp
    pointer_params_of_template.hpp
)

add_executable(main_ctor_template
    main_ctor_template.cpp
    ctor_template.hpp
)

add_executable(main_how_to_use_typename
    main_how_to_use_typename.cpp
    how_to_use_typename.hpp
)