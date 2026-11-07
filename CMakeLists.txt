# CMakeLists.txt (any OS: Windows, Linux, macOS) - Student grade calculator v1.0
#
#   cmake -S . -B build
#   cmake --build build --config Release
#
# Three programs are built from the SAME sources; only the container changes
# (see container.h):  students_vector, students_list, students_deque.

cmake_minimum_required(VERSION 3.10)
project(StudentsGradeCalculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Benchmarks only make sense with optimisation: default to Release.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(SOURCES
    main.cpp
    Student.cpp
    file.cpp
    process.cpp
    test.cpp
)

function(add_students_target target definition)
    add_executable(${target} ${SOURCES})
    if(definition)
        target_compile_definitions(${target} PRIVATE ${definition})
    endif()
    if(MSVC)
        target_compile_options(${target} PRIVATE /W3)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra)
    endif()
endfunction()

add_students_target(students_vector "")
add_students_target(students_list   USE_LIST)
add_students_target(students_deque  USE_DEQUE)
