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
add_library(nullptr_fix INTERFACE src/utils/nullptr_fix/nullptr_fix.h)
target_include_directories(nullptr_fix INTERFACE src/utils/nullptr_fix)
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

if(MATH_LIBRARY)
    #region floating_pointer_utils
    add_library(floating_pointer_utils
            src/utils/floating_pointer/floating_pointer_utils.c
            src/utils/floating_pointer/floating_pointer_utils.h)
    target_include_directories(floating_pointer_utils
            PUBLIC src/utils/floating_pointer)
    #endregion floating_pointer_utils

    #region simple_linear_regression
    add_library(simple_linear_regression
            src/machine_learning/simple_linear_regression/v1/simple_linear_regression.c
            src/machine_learning/simple_linear_regression/v1/simple_linear_regression.h)
    target_include_directories(simple_linear_regression
            PUBLIC src/machine_learning/simple_linear_regression/v1)
    target_link_libraries(simple_linear_regression
            PUBLIC floating_pointer_utils
            PRIVATE ${MATH_LIBRARY}
            PRIVATE nullptr_fix)

    add_executable(assert_simple_linear_regression test/assert_simple_linear_regression.c)
    target_link_libraries(assert_simple_linear_regression simple_linear_regression nullptr_fix)

    add_test(test_simple_linear_regression assert_simple_linear_regression)
    #endregion simple_linear_regression

    #region simple_linear_regression_v2
    add_library(simple_linear_regression_v2
            src/machine_learning/simple_linear_regression/v2/simple_linear_regression_v2.c
            src/machine_learning/simple_linear_regression/v2/simple_linear_regression_v2.h)
    target_include_directories(simple_linear_regression_v2
            PUBLIC src/machine_learning/simple_linear_regression/v2)
    target_link_libraries(simple_linear_regression_v2
            PUBLIC floating_pointer_utils
            PRIVATE ${MATH_LIBRARY}
            PRIVATE nullptr_fix)

    add_executable(assert_simple_linear_regression_v2 test/assert_simple_linear_regression_v2.c)
    target_link_libraries(assert_simple_linear_regression_v2 simple_linear_regression_v2)

    add_test(test_simple_linear_regression_v2 assert_simple_linear_regression_v2)
    #endregion simple_linear_regression_v2
endif()

#region string_utils
add_library(string_utils
        src/utils/string_utils/string_utils.c
        src/utils/string_utils/string_utils.h)
target_include_directories(string_utils PUBLIC src/utils/string_utils)

add_executable(assert_string_utils test/utils/string_utils/assert_string_utils.c)
target_link_libraries(assert_string_utils string_utils)

add_test(test_string_utils assert_string_utils)
#endregion string_utils

#region big_number
add_library(big_number
        src/utils/big_number/big_number.c
        src/utils/big_number/big_number.h)
target_include_directories(big_number PUBLIC src/utils/big_number)
target_link_libraries(big_number
        PRIVATE nullptr_fix
        PUBLIC string_utils)

add_executable(assert_big_number test/utils/big_number/assert_big_number.c)
target_link_libraries(assert_big_number big_number)

add_test(test_big_number assert_big_number)
#endregion big_number

#region big_decimal
add_library(big_decimal
        src/utils/big_decimal/big_decimal.c
        src/utils/big_decimal/big_decimal.h)
target_include_directories(big_decimal PUBLIC src/utils/big_decimal)
target_link_libraries(big_decimal PUBLIC string_utils)

add_executable(assert_big_decimal test/utils/big_decimal/assert_big_decimal.c)
target_link_libraries(assert_big_decimal big_decimal)

add_test(test_big_decimal assert_big_decimal)
#endregion big_decimal
