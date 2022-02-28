
#include <iostream>
#include <future>
#include <vector>
#include <gtest/gtest.h>

namespace {

int primes[] = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int nonPrimes[] = {0,4,6,8,9,10,12,14,15,16,18,20,21,22,24,25,26,27,28,30,32,33,34,35,36,
    38,39,40,42,44,45,46,48,49,50,51,52,54,55,56,57,58,60,62,63,64,65,66,68,69,70,72,74,
    75,76,77,78,80,81,82,84,85,86,87,88,90,91,92,93,94,95,96,98,99};
int highPrimes[] = {100000007,100000037,100000039,100000049,100000073,100000081};
int highNonPrimes[] = {100000000,100000001,100000002,100000003,100000004,100000005};

bool isPrime(int n)
{
    if (n < 1)
        return false;
    else if (n <= 3)
        return true;

    int i = 2;
    while (i < n)
        if (n%i++ == 0)
            return false;

    return true;
}

}

TEST(FutureTests, SimplePrimeTest)
{
    // Run all checks in a single thread
    for (int& n : primes)
        EXPECT_EQ(true, isPrime(n));

    for (int& n : nonPrimes)
        EXPECT_EQ(false, isPrime(n));

    for (int& n : highPrimes)
        EXPECT_EQ(true, isPrime(n));

    for (int& n : highNonPrimes)
        EXPECT_EQ(false, isPrime(n));
}

TEST(FutureTests, SimpleFutureTest)
{
    // Run all checks separately
    std::vector<std::future<bool>> primeFutures;
    std::vector<std::future<bool>> nonPrimeFutures;

    // Create an async call for each check and save returned future
    for (int& n : highPrimes)
        primeFutures.push_back(std::async(isPrime, n));

    for (int& n : highNonPrimes)
        nonPrimeFutures.push_back(std::async(isPrime, n));

    // get() result from the futures and verify results
    for (auto& ft : primeFutures)
        EXPECT_EQ(ft.get(), true);

    for (auto& ft : nonPrimeFutures)
        EXPECT_EQ(ft.get(), false);
}

void checkIsPrime(std::promise<bool>& pr, int n)
{
    pr.set_value(isPrime(n));
}

TEST(FutureTests, SimpleFutureAndPromiseTest)
{
    std::promise<bool> prom;
    std::future<bool> ft = prom.get_future();

    std::thread th (checkIsPrime, std::ref(prom), 100000081);

    EXPECT_EQ(ft.get(), true);
    th.join();
}
