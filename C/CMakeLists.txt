cmake_minimum_required(VERSION 3.29)
project(AlgorithmsPlaygroundInC C)

set(CMAKE_C_STANDARD 23)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g /Zi /W4 /WX")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g /Zi /W4 /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fPIE -fno-omit-frame-pointer -g -Wall -Wextra -Wpedantic")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fPIE -fno-omit-frame-pointer -g -Wall -Wextra -Wpedantic")
endif()

include(CTest)
enable_testing()

#region nullptr_fix
add_library(nullptr_fix INTERFACE src/nullptr_fix/nullptr_fix.h)
target_include_directories(nullptr_fix INTERFACE src/nullptr_fix)
#endregion nullptr_fix

#region linked_list_lib
add_library(linked_list_lib STATIC
        src/data_structures/linked_list/linked_list_lib.c
        src/data_structures/linked_list/linked_list_lib.h)
target_include_directories(linked_list_lib PUBLIC src/data_structures/linked_list)
target_link_libraries(linked_list_lib PRIVATE nullptr_fix)

add_executable(assert_linked_list_lib
        test/assert_linked_list_lib.c)
target_link_libraries(assert_linked_list_lib
        linked_list_lib
        nullptr_fix)

add_test(test_linked_list_lib assert_linked_list_lib)
#endregion linked_list_lib

#region doubly_linked_list_lib
add_library(doubly_linked_list_lib
        src/data_structures/doubly_linked_list/doubly_linked_list_lib.c
        src/data_structures/doubly_linked_list/doubly_linked_list_lib.h)
target_include_directories(doubly_linked_list_lib PUBLIC
        src/data_structures/doubly_linked_list)
target_link_libraries(doubly_linked_list_lib PRIVATE nullptr_fix)

add_executable(assert_doubly_linked_list_lib
        test/assert_doubly_linked_list_lib.c)
target_link_libraries(assert_doubly_linked_list_lib
        doubly_linked_list_lib
        nullptr_fix)

add_test(test_doubly_linked_list_lib assert_doubly_linked_list_lib)
#endregion doubly_linked_list_lib

#region vector_lib
add_library(vector_lib STATIC
        src/data_structures/vector/vector_lib.c
        src/data_structures/vector/vector_lib.h)
target_include_directories(vector_lib PUBLIC src/data_structures/vector)
target_link_libraries(vector_lib PRIVATE nullptr_fix)

add_executable(assert_vector_lib test/assert_vector_lib.c)
target_link_libraries(assert_vector_lib vector_lib nullptr_fix)

#add_test(test_vector_lib assert_vector_lib)
#endregion vector_lib

#region stack_lib
add_library(stack_lib STATIC
        src/data_structures/stack/stack_lib.c
        src/data_structures/stack/stack_lib.h)
target_include_directories(stack_lib PUBLIC src/data_structures/stack)
target_link_libraries(stack_lib
        PUBLIC vector_lib
        PRIVATE nullptr_fix)

add_executable(assert_stack_lib test/assert_stack_lib.c)
target_link_libraries(assert_stack_lib stack_lib nullptr_fix)

add_test(test_stack_lib assert_stack_lib)
#endregion stack_lib
