cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
# OFF(默认) 则 CMake 检测到编译器不支持 C++17 时不报错，而是默默调低到 C++14 给你用；为 ON 则发现不支持报错，更安全
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ON(默认) 表示启用 GCC 特有的一些扩展功能；OFF 则关闭 GCC 的扩展功能，只使用标准的 C++(兼容 MSVC)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILE_FEATURES OFF)

set(PROJECT_NAME template_cpp)
project(${PROJECT_NAME} VERSION 0.1.0)

if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(WARNING "This binary directory of CMake cannot be the same as source directory!")
endif()

# Release: -O3 -DNDEBUG
# Debug: -O0 -g
# MinSizeRel: -Os -DNDEBUG 
# RelWithDebInfo: -O2 -g -DNDEBUG
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

if (NOT MSVC) 
    find_program(CCACHE_PROGRAM ccache)
    if (CCACHE_PROGRAM)
        message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
    endif()
endif()

# src
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cc src/*.cpp inc/*.h)
# add_library(${PROJECT_NAME} SHARED ${srcs})
add_executable(${PROJECT_NAME} ${srcs})
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
target_include_directories(${PROJECT_NAME} PUBLIC inc)

# sub
# add_subdirectory()

# test
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Enable test")
    add_subdirectory(test)
endif()
