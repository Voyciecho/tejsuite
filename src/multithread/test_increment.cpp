
#include <iostream>
#include <mutex>
#include <thread>
#include <gtest/gtest.h>

namespace {

int sum;

// Simple add which is NOT thread safe
void addSimple(int x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    sum += x;
}

// Add mutex to the simple add to make it thread safe
std::mutex mtx;

void addLocked(int x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    mtx.lock();
    sum += x;
    mtx.unlock();
}

// Use atomic instead of a mutex
std::atomic<int> sumAtomic;

void addAtomic(int x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    sumAtomic += x;
}


// Don't use any locking and make it thread safe by design.
// So don't share data between threads, which is a bit faster during write,
// as there's no locking mechanism, but much slower on read, plus very mem hungry.
int separateSums[10000] = {0,};

void addNonLocked(int id, int x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    separateSums[id] += x;
}

int getSum()
{
    int result = 0;

    for (int& x : separateSums)
        result += x;

    return result;
}

}

TEST(IncrementTests, SimpleIncrementTest)
{
    sum = 0;
    std::thread threads[10000];

    for (int i=0; i<10000; ++i)
        threads[i] = std::thread(addSimple, i);

    for (auto& thread : threads)
        thread.join();

    if (sum == 49995000)
        std::cout << "Final sum is correct. You were lucky\n";
    else
        std::cout << "Final sum: " << sum << " while it should be 49995000\n";
    EXPECT_LE(sum, 49995000);
}

TEST(IncrementTests, LockedIncrementTest)
{
    sum = 0;
    std::thread threads[10000];

    for (int i=0; i<10000; ++i)
        threads[i] = std::thread(addLocked, i);

    for (auto& thread : threads)
        thread.join();

    std::cout << "Final sum: " << sum << "\n";
    EXPECT_EQ(sum, 49995000);
}

TEST(IncrementTests, AtomicIncrementTest)
{
    sumAtomic = 0;
    std::thread threads[10000];

    for (int i=0; i<10000; ++i)
        threads[i] = std::thread(addAtomic, i);

    for (auto& thread : threads)
        thread.join();

    std::cout << "Final sum: " << sumAtomic << "\n";
    EXPECT_EQ(sum, 49995000);
}

TEST(IncrementTests, NonlockedIncrementTest)
{
    sum = 0;
    std::thread threads[10000];

    for (int i=0; i<10000; ++i)
        threads[i] = std::thread(addNonLocked, i, i);

    for (auto& thread : threads)
        thread.join();

    std::cout << "Final sum: " << getSum() << "\n";
    EXPECT_EQ(getSum(), 49995000);
}
