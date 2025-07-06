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
target_include_directories(vectrix INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        $<INSTALL_INTERFACE:include>
)
target_compile_definitions(vectrix INTERFACE $<$<BOOL:${VTX_USE_CPP20}>:VTX_CPP20>)

add_executable(VTXBuild src/main.cpp)
target_link_libraries(VTXBuild PRIVATE vectrix)

# Add unit tests
option(BUILD_TESTING "Build the tests" ON)

if(BUILD_TESTING)
    add_subdirectory(extern/Catch2)
    enable_testing()
    add_compile_definitions(VTX_DEFAULT_FILL0)

    file(GLOB_RECURSE TEST_SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
    )
    add_executable(VTXTests ${TEST_SOURCES})

    # Link to Catch2
    target_link_libraries(VTXTests PRIVATE vectrix Catch2::Catch2WithMain)
    target_include_directories(VTXTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

    add_test(NAME vectrix_tests COMMAND VTXTests)
    #target_compile_definitions(tests PRIVATE
    #        $<$<BOOL:${VTX_USE_CPP20}>:VTX_CPP20>
    #) # TODO: Think about this definitions
endif()
