
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <gtest/gtest.h>

namespace {

class Event
{
public:
    Event() : run(false) {}
    void wait()
    {
        std::unique_lock<std::mutex> lck(mtx);
        while (!run) cv.wait(lck);
    }
    void signal()
    {
        std::unique_lock<std::mutex> lck(mtx);
        run = true;
        cv.notify_all();
    }
    bool isRun() const
    {
        return run;
    }

private:
    bool run;
    std::condition_variable cv;
    std::mutex mtx;
};

void waitForEvent(Event& e)
{
    EXPECT_EQ(e.isRun(), false);
    e.wait();
    EXPECT_EQ(e.isRun(), true);
}

}

TEST(ConditionVariableEventClassTests, ConditionVariableEventClassWithSeparateFunctionTest)
{
    Event e;
    // Use a separate function: waitForEvent()
    std::thread th(waitForEvent, std::ref(e));                                            // objects cannot be passed to thread by value
                                                                                          // std::ref will wrap e into an object, which is it's reference
                                                                                          // and can be passed safely to the thread's function
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_EQ(e.isRun(), false);
    e.signal();
    EXPECT_EQ(e.isRun(), true);
    th.join();
    EXPECT_EQ(e.isRun(), true);
}

TEST(ConditionVariableEventClassTests, ConditionVariableEventClassTest)
{
    Event e;
    // Use Event's method: Event::wait()
    std::thread th(&Event::wait, std::ref(e));                                            // members methods can also be passed in the same way
                                                                                          // with std::ref
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_EQ(e.isRun(), false);
    e.signal();
    EXPECT_EQ(e.isRun(), true);
    th.join();
    EXPECT_EQ(e.isRun(), true);
}

TEST(ConditionVariableEventClassTests, ConditionVariableEventClassWithBindTest)
{
    Event e;
    // Use Event's method: Event::wait() with std::bind
    auto bound_fn = std::bind(&Event::wait, std::placeholders::_1);                       // binds Event member method with Event object, _1 arg is the object
    std::thread th = std::thread(bound_fn, &e);                                           // pass bound fn with the object

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_EQ(e.isRun(), false);
    e.signal();
    EXPECT_EQ(e.isRun(), true);
    th.join();
    EXPECT_EQ(e.isRun(), true);
}

TEST(ConditionVariableEventClassTests, ConditionVariableEventClassManyThreadsTest)
{
    Event e;
    std::thread threads[10];

    // Create 10 threads and let all of them wait for signal()
    for (int i=0; i<10; ++i)
        threads[i] = std::thread(std::bind(&Event::wait, std::placeholders::_1), &e);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_EQ(e.isRun(), false);
    e.signal();
    EXPECT_EQ(e.isRun(), true);
    for (auto& th : threads)
        th.join();
    EXPECT_EQ(e.isRun(), true);
}
