cmake_minimum_required(VERSION 3.29)
project(AlgorithmsPlaygroundInCpp CXX)
set(CMAKE_CXX_STANDARD 26)
set(CXX_STANDARD 26)

if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
     -fsanitize=address -g /Zi /W4 /WX \
     /wd4566")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
     -fsanitize=address \
     -fPIE \
     -fno-omit-frame-pointer \
     -g \
     -Wall \
     -Wextra \
     -Wpedantic \
     -Wno-keyword-macro \
     -Wno-gnu-pointer-arith \
     -Wno-unknown-pragmas")
endif()

include(CTest)
enable_testing()

#region linked_list
add_library(cpp_linked_list
        INTERFACE src/data_structures/linked_list/LinkedList.hpp)
target_include_directories(cpp_linked_list
        INTERFACE src/data_structures/linked_list)

add_executable(assert_cpp_linked_list test/assert_cpp_linked_list.cpp)
target_link_libraries(assert_cpp_linked_list cpp_linked_list)

add_test(test_cpp_linked_list assert_cpp_linked_list)
#endregion linked_list
