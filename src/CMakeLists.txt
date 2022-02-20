
add_executable(tejsuite
    main.cpp
    test_simple.cpp
)

target_link_libraries(tejsuite gtest)
