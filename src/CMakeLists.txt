
add_executable(tejsuite
    main.cpp
    test_simple.cpp
    test_fibonacci.cpp
)

target_link_libraries(tejsuite gtest)
