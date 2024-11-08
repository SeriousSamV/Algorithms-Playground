cmake_minimum_required(VERSION 3.29)
project(AlgorithmsPlaygroundInC C)

set(CMAKE_C_STANDARD 23)

find_library(MATH_LIBRARY m)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

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

#region queue_lib
add_library(queue_lib STATIC src/data_structures/queue/queue_lib.c src/data_structures/queue/queue_lib.h)
target_include_directories(queue_lib PUBLIC src/data_structures/queue)
target_link_libraries(queue_lib
        PUBLIC linked_list_lib
        PRIVATE nullptr_fix)

add_executable(assert_queue_lib test/assert_queue_lib.c)
target_link_libraries(assert_queue_lib queue_lib nullptr_fix)

add_test(test_queue_lib assert_queue_lib)
#endregion queue_lib

#region tree_lib
add_library(tree_lib src/data_structures/tree/tree_lib.c src/data_structures/tree/tree_lib.h)
target_include_directories(tree_lib PUBLIC src/data_structures/tree)
target_link_libraries(tree_lib PRIVATE nullptr_fix)

add_executable(assert_tree_lib test/assert_tree_lib.c)
target_link_libraries(assert_tree_lib tree_lib nullptr_fix)

add_test(test_tree_lib assert_tree_lib)
#endregion tree_lib

#region simple_linear_regression
if(MATH_LIBRARY)
    add_library(simple_linear_regression
            src/machine_learning/simple_linear_regression.c
            src/machine_learning/simple_linear_regression.h)
    target_include_directories(simple_linear_regression PUBLIC src/machine_learning)
    target_link_libraries(simple_linear_regression
            PUBLIC ${MATH_LIBRARY}
            PRIVATE nullptr_fix)

    add_executable(assert_simple_linear_regression test/assert_simple_linear_regression.c)
    target_link_libraries(assert_simple_linear_regression simple_linear_regression nullptr_fix)

    add_test(test_simple_linear_regression assert_simple_linear_regression)
endif()
#endregion simple_linear_regression
