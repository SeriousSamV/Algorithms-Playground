cmake_minimum_required(VERSION 3.29)
project(AlgorithmsPlaygroundInC C)

set(CMAKE_C_STANDARD 23)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

include(CTest)
enable_testing()

add_library(linked_list_lib STATIC src/linked_list/linked_list_lib.c src/linked_list/linked_list_lib.h)
target_include_directories(linked_list_lib PUBLIC src/linked_list)

add_executable(assert_linked_list_lib test/assert_linked_list_lib.c)
target_link_libraries(assert_linked_list_lib linked_list_lib)

add_test(test_linked_list_lib assert_linked_list_lib)
