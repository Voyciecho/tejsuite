
#include <iostream>
#include <mutex>
#include <thread>
#include <gtest/gtest.h>

namespace {

std::mutex mtx;
std::recursive_mutex rmtx;

void printLine(char c)
{
    static int idx = 0;

    EXPECT_EQ(idx%50, 0);

    for (int i=0; i<50; ++i, ++idx)
        std::cout << c;
    std::cout << "\n";

    EXPECT_EQ(idx%50, 0);
}

void printLineUnderMutex(char c)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Mutex is a lockable object allowing exclusive access to a critical section
    mtx.lock();
    printLine(c);
    mtx.unlock();
}

void printLineUnderRecursiveMutex(char c)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Recursive Mutex can be lock on multiple levels by the same thread
    rmtx.lock();
    rmtx.lock();
    printLine(c);
    rmtx.unlock();
    rmtx.unlock();
}

void printLineUnderLockGuard(char c)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Lock Guard - object for managing a mutex object by keeping it always locked
    // Lock Guard is locked/unlocked on create/destroy following RAII - Resource Acquisition Is Initialization
    std::lock_guard<std::mutex> lck(mtx);
    printLine(c);
}

void printLineUnderUniqueLock(char c)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Unique Lock - object for managing a unique ownership of a mutex object
    // It's also RAII, but it can be locked&unlocked - used in i.e. ConditionVariable
    std::unique_lock<std::mutex> lck(mtx);
    printLine(c);
}

void printLineUnderDeferredUniqueLock(char c)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Create an unlocked Unique Lock, in order to lock it later
    std::unique_lock<std::mutex> lck(mtx, std::defer_lock);

    lck.lock();
    printLine(c);

    // automatic unlock on lck destroy
}

void printLineUnderAdoptedUniqueLock(char c)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Create a locked Unique Lock that adopts an already locked mutex
    mtx.lock();
    std::unique_lock<std::mutex> lck(mtx, std::adopt_lock);
    printLine(c);
}

void concurentPrint(std::function<void(char)> func)
{
    std::thread threads[10];

    for (int i=0; i<10; ++i)
        threads[i] = std::thread(func, '0' + i);

    for (auto& th: threads)
        th.join();
}

}

TEST(LockingTests, SimpleMutexTest)
{
    concurentPrint(printLineUnderMutex);
}

TEST(LockingTests, RecursiveMutexTest)
{
    concurentPrint(printLineUnderRecursiveMutex);
}

TEST(LockingTests, SimpleLockGuardTest)
{
    concurentPrint(printLineUnderLockGuard);
}

TEST(LockingTests, SimpleUniqueLockTest)
{
    concurentPrint(printLineUnderUniqueLock);
}

TEST(LockingTests, DeferredUniqueLockTest)
{
    concurentPrint(printLineUnderDeferredUniqueLock);
}

TEST(LockingTests, AdoptedUniqueLockTest)
{
    concurentPrint(printLineUnderAdoptedUniqueLock);
}



