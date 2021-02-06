cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch3 ==========")

# # Header Files
# file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# message("Header Files: ${EXE_INCLUDES}")

# # Source Files
# file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# message("Source Files: ${EXE_SOURCES}")

add_executable(iterator_func
    main_iterator_func.cpp
    iterator_func.hpp
)

add_executable(functor
    main_functor.cpp
    functor.hpp
)

add_executable(generic_program
    main_generic_program.cpp
    generic_program.hpp
)

add_executable(helper_func_for_predict
    main_helper_func_for_predict.cpp
    helper_func_for_predict.hpp
)

add_executable(tag_dispatch
    main_tag_dispatch.cpp
    tag_dispatch.hpp    
)

add_executable(params_extension
    main_params_extension.cpp
    params_extension.hpp
)

