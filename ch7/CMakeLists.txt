cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch7 ==========")

# # Header Files
# file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# message("Header Files: ${EXE_INCLUDES}")

# # Source Files
# file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# message("Source Files: ${EXE_SOURCES}")

add_executable(concept
    main_concept.cpp
    concept.hpp
)

add_executable(concept_overload
    main_concept_overload.cpp
    concept_overload.hpp
)
target_compile_features(concept_overload
    PUBLIC cxx_std_20
)

add_executable(specialize_template_by_concept
    main_specialize_template_by_concept.cpp
    specialize_template_by_concept.hpp
)
target_compile_features(specialize_template_by_concept
    PUBLIC cxx_std_20
)