cmake_minimum_required(VERSION 3.14.0)
project(TemplateTechnique LANGUAGES CXX VERSION 0.1.0)

###############################################################################
# Version
###############################################################################
message(STATUS "========== [START] Version Management ==========")
# CMake Version
message(STATUS "CMake Version: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION}")

# プロジェクト Version
file(STRINGS ${CMAKE_SOURCE_DIR}/VERSION.txt versions NEWLINE_CONSUME)
string(REGEX REPLACE [[^([A-z0-9.\-_]+).*$]] [[\1]] version ${versions})
string(REGEX REPLACE [[^([0-9]+)\.([0-9]+)\.(.*)$]] [[\1]] version_major ${version})
string(REGEX REPLACE [[^([0-9]+)\.([0-9]+)\.(.*)$]] [[\2]] version_minor ${version})
string(REGEX REPLACE [[^([0-9]+)\.([0-9]+)\.(.*)$]] [[\3]] version_patch ${version})

message(STATUS "========== [END] Version Management ==========")

###############################################################################
# 前処理
###############################################################################
message(STATUS "========== [START] Preprocessing ==========")

# pythonコマンドをCMakeで使えるようにする
set(PYTHON_COMMAND_NAME "python3") # どのインタープリタが選ばれるかはPCの設定次第. もっと詳細設定をコマンドライン引数から与えても良いと思う.
find_program(PYTHON_INTERPRETER ${PYTHON_COMMAND_NAME})
if(NOT EXISTS ${PYTHON_INTERPRETER})
    message(FATAL_ERROR "python [${PYTHON_INTERPRETER}] not found.")
    error() # Place Unknown command to stop cmake process here.
endif()
set(PYTHON_COMMAND "${PYTHON_INTERPRETER}")
message(STATUS "python interpreter: ${PYTHON_INTERPRETER}")

message(STATUS "========== [END] Preprocessing ==========")

###############################################################################
# 全ターゲットに影響を与えるオプション
###############################################################################
message(STATUS "========== [START] C++ All Target Options ==========")

# ========== Options ==========
option(BUILD_OPENMP "Enable/Disable OpenMP" ON)
option(BUILD_CPP_TEST "Building test" OFF)
option(BUILD_CPP_SHARED_LIBS "Enable/Disable shared libraries" ON)

# Global Test flag
if(BUILD_CPP_TEST)
    set(BUILD_TESTING ON)
else()
    set(BUILD_TESTING OFF)
endif()

# Global Shared lib flag
if(BUILD_CPP_SHARED_LIBS)
    set(BUILD_CPP_SHARED_LIBS ON)
else()
    set(BUILD_CPP_SHARED_LIBS OFF)
endif()

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message("CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

# プラットフォーム毎のコンパイラオプション(マルチ・コンフィギュレーションに対応)
if (MSVC)
    message(STATUS "Compiler: MSVC in Windows")

    # Build Options
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # デフォルトの`/W[0-4]`を削除
    set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /GR /EHsc /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "/Ob0 /Od /MDd /Zi /RTC1") # /MDd or /Od が指定されている場合、#include <windows>内部で_DEBUGマクロが定義される
    set(CMAKE_CXX_FLAGS_RELEASE "/Ob2 /O2 /MD /DNDEBUG") # /DNDEBUGマクロはstatic_assert()で利用する
    set(CMAKE_CXX_FLAGS_MINSIZEREL "/O1 /MD /DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Od /MDd /Zi /RTC1")

    if(BUILD_OPENMP)
        add_compile_options("$<$<C_COMPILER_ID:MSVC>:/openmp>")
        add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/openmp>")
    endif()

    # ソースコードでUTF-8を使う(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

    # C++11以降を利用した場合にマクロ変数__cplusplusの値を利用中のC++バージョンに合わせる(つけないとC++98相当の値になる)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>")

    # オブジェクトファイル(*.obj)のサイズ制限を解放
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/bigobj>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/bigobj>")

    # プリコンパイル済みヘッダーの使用(/Yu)を全体に設定
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yu")

elseif(APPLE)

message(STATUS "Compiler: Clang in macOS")    

    message(FATAL_ERROR "No Implementation of Build Rule on Clang with LLVM in macOS.")

else()
    message(STATUS "Compiler: GCC in Linux")

    # 詳細情報の表示
    set(CMAKE_VERBOSE_MAKEFILE ON)

    # Build Options(マルチコンフィギュレーション:visual studio対応)
    set(CMAKE_CXX_FLAGS "-O1")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")

    # C++標準に準拠しない拡張機能を無効化
    string(APPEND CMAKE_CXX_FLAGS " --pedantic-errors")

    # https://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings/9862800#9862800
    string(APPEND CMAKE_CXX_FLAGS " -pedantic")
    string(APPEND CMAKE_CXX_FLAGS " -Wall")
    # string(APPEND CMAKE_CXX_FLAGS " -Wextra")
    # string(APPEND CMAKE_CXX_FLAGS " -Wcast-align")
    # string(APPEND CMAKE_CXX_FLAGS " -Wcast-qual")
    # string(APPEND CMAKE_CXX_FLAGS " -Wctor-dtor-privacy")
    # string(APPEND CMAKE_CXX_FLAGS " -Wdisabled-optimization")
    # string(APPEND CMAKE_CXX_FLAGS " -Wformat=2 ")
    # string(APPEND CMAKE_CXX_FLAGS " -Winit-self")
    # string(APPEND CMAKE_CXX_FLAGS " -Wlogical-op")
    # string(APPEND CMAKE_CXX_FLAGS " -Wmissing-declarations")
    # string(APPEND CMAKE_CXX_FLAGS " -Wmissing-include-dirs")
    # string(APPEND CMAKE_CXX_FLAGS " -Wnoexcept")
    # string(APPEND CMAKE_CXX_FLAGS " -Wold-style-cast")
    # string(APPEND CMAKE_CXX_FLAGS " -Woverloaded-virtual")
    # string(APPEND CMAKE_CXX_FLAGS " -Wredundant-decls")
    # string(APPEND CMAKE_CXX_FLAGS " -Wshadow")
    # string(APPEND CMAKE_CXX_FLAGS " -Wsign-conversion")
    # string(APPEND CMAKE_CXX_FLAGS " -Wsign-promo")
    # string(APPEND CMAKE_CXX_FLAGS " -Wstrict-null-sentinel")
    # string(APPEND CMAKE_CXX_FLAGS " -Wstrict-overflow=5")
    # string(APPEND CMAKE_CXX_FLAGS " -Wswitch-default")
    # string(APPEND CMAKE_CXX_FLAGS " -Wundef")
    # string(APPEND CMAKE_CXX_FLAGS " -Werror")
    # string(APPEND CMAKE_CXX_FLAGS " -Wno-unused")

endif()

message("---------- Compiler Options for Multi Configuration such as XCode, Visual Studio ----------")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CMAKE_CXX_FLAGS_MINSIZEREL: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message(STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

message(STATUS "========== [END] C++ All Target Options ==========")

###############################################################################
# C++ core
###############################################################################
message(STATUS "========== [START] C++ Build Core ==========")

# ========== Library File ==========


# ========== Executable File ==========
add_subdirectory(ch1)
add_subdirectory(ch2)
add_subdirectory(ch3)
add_subdirectory(ch4)
add_subdirectory(ch5)
add_subdirectory(ch6)
add_subdirectory(ch7)
add_subdirectory(ch8)
add_subdirectory(ch9)
add_subdirectory(ch10)
add_subdirectory(ch11)

message(STATUS "========== [END] C++ Build Core ==========")

###############################################################################
# C++ Testing
###############################################################################
message(STATUS "========== [START] C++ Build Test ==========")
include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

message(STATUS "========== [END] C++ Build Test ==========")