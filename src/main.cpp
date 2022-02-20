
#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    std::cout << "Test Experiment and enJoy Suite - Hello World\n";

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
