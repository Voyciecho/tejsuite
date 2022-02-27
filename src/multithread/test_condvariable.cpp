
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <gtest/gtest.h>

namespace {

bool run = false;
std::condition_variable cv;
std::mutex mtx;

void waitForEvent()
{
    std::unique_lock<std::mutex> lck(mtx);
    while (!run) cv.wait(lck);
}

void signalEvent()
{
    std::unique_lock<std::mutex> lck(mtx);
    run = true;
    cv.notify_all();
}

}

TEST(ConditionVariableSimpleTests, SimpleConditionVariableTest)
{
    std::thread th(waitForEvent);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_EQ(run, false);
    signalEvent();
    EXPECT_EQ(run, true);
    th.join();
    EXPECT_EQ(run, true);
}
