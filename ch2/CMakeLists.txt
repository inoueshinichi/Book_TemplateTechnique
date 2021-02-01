cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch2 ==========")

add_executable(main_stack
    main_stack.cpp
    template_stack.hpp
    template_stack.cpp
)

add_executable(pointer_params
    main_pointer_params.cpp
    pointer_params_of_template.hpp
)

add_executable(ctor_template
    main_ctor_template.cpp
    ctor_template.hpp
)

add_executable(how_to_use_typename
    main_how_to_use_typename.cpp
    how_to_use_typename.hpp
)

add_executable(specialization
    main_specialization.cpp
    specialization.hpp
)

add_executable(template_template_params
    main_template_template_params.cpp
    template_template_params.hpp
)

add_executable(valiadic_template_params
    main_valiadic_template_params.cpp
    valiadic_template_params.hpp
)