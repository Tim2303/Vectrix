cmake_minimum_required(VERSION 3.12)
project(vectrix LANGUAGES CXX)

# Base C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optional: turn on C++20 features
option(VTX_USE_CPP20 "Enable C++20-specific features in vectrix" OFF)

if(VTX_USE_CPP20)
    # Check C++20 support
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)
    if(COMPILER_SUPPORTS_CXX20)
        set(CMAKE_CXX_STANDARD 20)
        add_compile_definitions(VTX_CPP20)
    else()
        message(FATAL_ERROR "C++20 not supported by your compiler.")
    endif()
endif()

# Main library
add_library(vectrix INTERFACE)
target_include_directories(vectrix INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(vectrix INTERFACE $<$<BOOL:${VTX_USE_CPP20}>:VTX_CPP20>)
