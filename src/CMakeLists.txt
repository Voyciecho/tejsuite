
add_executable(tejsuite
    main.cpp
    test_simple.cpp
    test_virtual.cpp
    test_iterate_array.cpp
    test_diamond.cpp
    test_fibonacci.cpp
    test_linked_list.cpp
    test_encode_num_chars.cpp
    multithread/test_mutex.cpp
    multithread/test_increment.cpp
    multithread/test_lockguard.cpp
    multithread/test_condvariable.cpp
    multithread/test_condvariableeventclass.cpp
    multithread/test_future.cpp
)

target_link_libraries(tejsuite gtest)
