cmake_minimum_required(VERSION 3.29)
project(AlgorithmsPlaygroundInC C)

set(CMAKE_C_STANDARD 23)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wpedantic -Werror")
endif()

include(CTest)
enable_testing()

# region nullptr_fix
add_library(nullptr_fix INTERFACE src/nullptr_fix/nullptr_fix.h)
target_include_directories(nullptr_fix INTERFACE src/nullptr_fix)
# endregion nullptr_fix

# region linked_list_lib
add_library(linked_list_lib STATIC
        src/linked_list/linked_list_lib.c
        src/linked_list/linked_list_lib.h)
target_include_directories(linked_list_lib PUBLIC src/linked_list)
target_link_libraries(linked_list_lib PRIVATE nullptr_fix)

add_executable(assert_linked_list_lib
        test/assert_linked_list_lib.c)
target_link_libraries(assert_linked_list_lib
        linked_list_lib
        nullptr_fix)

add_test(test_linked_list_lib assert_linked_list_lib)
# endregion linked_list_lib

# region doubly_linked_list_lib
add_library(doubly_linked_list_lib
        src/doubly_linked_list/doubly_linked_list_lib.c
        src/doubly_linked_list/doubly_linked_list_lib.h)
target_include_directories(doubly_linked_list_lib PUBLIC
        src/doubly_linked_list)
target_link_libraries(doubly_linked_list_lib PRIVATE nullptr_fix)

add_executable(assert_doubly_linked_list_lib
        test/assert_doubly_linked_list_lib.c)
target_link_libraries(assert_doubly_linked_list_lib
        doubly_linked_list_lib
        nullptr_fix)

add_test(test_doubly_linked_list_lib assert_doubly_linked_list_lib)
# endregion doubly_linked_list_lib
