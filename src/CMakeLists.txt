
add_executable(tejsuite
    main.cpp
    test_simple.cpp
    test_iterate_array.cpp
    test_fibonacci.cpp
    multithread/test_lockguard.cpp
    multithread/test_mutex.cpp
)

target_link_libraries(tejsuite gtest)
