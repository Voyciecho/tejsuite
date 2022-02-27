
add_executable(tejsuite
    main.cpp
    test_simple.cpp
    test_iterate_array.cpp
    test_fibonacci.cpp
    multithread/test_mutex.cpp
    multithread/test_condvariable.cpp
    multithread/test_condvariableeventclass.cpp
    multithread/test_lockguard.cpp
)

target_link_libraries(tejsuite gtest)
