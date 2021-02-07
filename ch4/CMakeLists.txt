cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch4 ==========")

# # Header Files
# file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# message("Header Files: ${EXE_INCLUDES}")

# # Source Files
# file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# message("Source Files: ${EXE_SOURCES}")

add_executable(meta_func 
    main_meta_func.cpp
    meta_func.hpp
)

add_executable(meta_func2
    main_meta_func2.cpp
    meta_func2.hpp
)

add_executable(compile_if
    main_compile_if.cpp
    compile_if.hpp
)

add_executable(type_list
    main_type_list.cpp
    type_list.hpp
)