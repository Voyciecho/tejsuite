
#include <iostream>
#include <mutex>
#include <thread>
#include <gtest/gtest.h>

namespace {

std::mutex mtx;
int idx = 0;

void printLine(char c)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    mtx.lock();
    EXPECT_EQ(idx%50, 0);

    for (int i=0; i<50; ++i, ++idx)
        std::cout << c;
    std::cout << "\n";

    EXPECT_EQ(idx%50, 0);
    mtx.unlock();
}

void concurentPrint()
{
    std::thread threads[10];

    for (int i=0; i<10; ++i)
        threads[i] = std::thread(printLine, '0' + i);

    for (auto& th: threads)
        th.join();
}

}

TEST(MutexTest, SimpleMutexTest)
{
    concurentPrint();
}
