
#include <iostream>
#include <gtest/gtest.h>

int iterateForLoopWithSizeOf()
{
    // Simple for loop with the use of sizeof

    int sum = 0;
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
        sum += arr[i];

    return sum;
}

int iterateForLoopWithIterator()
{
    // Simple for loop accessed via Iterator

    int sum = 0;
    std::array<int, 10> arr {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (auto it = arr.begin(); it != arr.end(); ++it)
        sum += *it;

    return sum;
}

int iterateStdForEachLoop()
{
    // std::for_each calls a lambda func with each element, which captures sum's reference to operate on it

    int sum = 0;
    std::array<int, 10> arr {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::for_each(arr.begin(), arr.end(), [&sum] (int& element) {
        sum  += element;
    });

    return sum;
}

int iterateRangeBasedForLoop()
{
    // Range-based for loop - since C++11

    int sum = 0;
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Iterate through arr, const elements cannot be changed
    for (const int element : arr)
        sum += element;

    // Passed by value, so elements are not changed
    for (int element : arr)
        element = 0;
    EXPECT_EQ(arr[9], 9);

    // Passed by reference, so elements are changed
    for (int &element : arr)
        element = 0;
    EXPECT_EQ(arr[9], 0);

    return sum;
}

TEST(IterateArrayTest, IterateForLoopWithSizeOfTest) {
    EXPECT_EQ(iterateForLoopWithSizeOf(), 45);
}

TEST(IterateArrayTest, IterateForLoopWithIteratorTest) {
    EXPECT_EQ(iterateForLoopWithIterator(), 45);
}

TEST(IterateArrayTest, IterateStdForEachTest) {
    EXPECT_EQ(iterateStdForEachLoop(), 45);
}

TEST(IterateArrayTest, IterateRangeBasedForLoopTest) {
    EXPECT_EQ(iterateRangeBasedForLoop(), 45);
}
