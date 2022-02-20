
#include <iostream>
#include <map>
#include <gtest/gtest.h>

std::map<int, int> testData {{0,0}, {1,1}, {2,1}, {3,2}, {4,3}, {5,5}, {6,8}, {7,13}, {8,21}, {9,34}, {10, 55},
                             {11,89}, {12,144}, {13,233}, {15,610}, {20,6765}, {30,832040}, {40,102334155}};

int fibonacci(int n)
{
    int f      = 0;
    int last_1 = 0;
    int last_2 = 1;

    for (int i=0; i<n; ++i)
    {
        f = last_1 + last_2;
        last_2 = last_1;
        last_1 = f;
    }

    return f;
}

int fibonacciRecursive(int n)
{
    if (n==0) return 0;
    if (n==1) return 1;
    return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
}

TEST(FibonacciTest, FibonacciSimpleTest)
{
    for (const auto& [key, value] : testData)
    {
        std::cout<<"["<<key<<"] "<< value << "  " << fibonacci(key) << "\n";
        EXPECT_EQ(value, fibonacciRecursive(key));
    }
}

TEST(FibonacciTest, FibonacciRecursiveTest)
{
    for (const auto& [key, value] : testData)
    {
        std::cout<<"["<<key<<"] "<< value << "  " << fibonacciRecursive(key) << "\n";
        EXPECT_EQ(value, fibonacciRecursive(key));
    }
}
