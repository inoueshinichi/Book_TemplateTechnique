cmake_minimum_required(VERSION 3.14.0)
message(STATUS "========== [START] ch6 ==========")

# # Header Files
# file(GLOB EXE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# message("Header Files: ${EXE_INCLUDES}")

# # Source Files
# file(GLOB EXE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# message("Source Files: ${EXE_SOURCES}")

add_executable(policy1
    main_policy1.cpp
    policy1.hpp
)

add_executable(named_policy
    named_policy.hpp
    main_named_policy.cpp
)

add_executable(std_named_policy
    main_std_named_policy.cpp
    std_named_policy.hpp
)

# # Boostライブラリを使用
# set(Boost_USE_STATIC_LIBS        ON)
# set(Boost_USE_MULTITHREADED      ON)
# set(Boost_USE_STATIC_RUNTIME   ON)

# find_package(Boost 1.7.1 REQUIRED COMPONENTS 
#     date_time
# )
# message("## Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")  # デバッグ用：解決したパスを表示
# message("## Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")  # デバッグ用：解決したパスを表示

