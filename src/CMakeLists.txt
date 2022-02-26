
add_executable(tejsuite
    main.cpp
    test_simple.cpp
    test_iterate_array.cpp
    test_fibonacci.cpp
    test_lockguard.cpp
)

target_link_libraries(tejsuite gtest)
