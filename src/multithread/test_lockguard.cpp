
#include <iostream>
#include <mutex>
#include <thread>
#include <gtest/gtest.h>

class BankAccount
{
public:
    BankAccount() : balance(0)
    {}

    int getBalance()
    {
        return balance;
    }

    virtual void payIn(int amount)
    {
        balance += amount;
    }

protected:
    int balance;
};

class BankAccountThreadSafe : public BankAccount
{
public:
    virtual void payIn(int amount)
    {
        std::lock_guard<std::mutex> lock(mtx);
        BankAccount::payIn(amount);
    }

private:
    std::mutex mtx;
};


void transfer(BankAccount *acc, int amount)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    acc->payIn(amount);
}

TEST(BankAccountTest, SimpleTest)
{
    BankAccount account = BankAccount();
    std::vector<std::thread> transfers;

    for (int i=0; i<100; ++i)
        transfers.push_back(std::thread(transfer, &account, i));

    for (int i=0; i<100; ++i)
        transfers[i].join();

    for (int i=0; i<100; ++i)
        transfers.pop_back();

    std::cout << "Failed Balance (anything up to 4950): " << account.getBalance() << "\n";

    EXPECT_GE(4950, account.getBalance());
}

TEST(BankAccountTest, ThreadSafeTest)
{
    BankAccountThreadSafe account = BankAccountThreadSafe();
    std::vector<std::thread> transfers;

    for (int i=0; i<100; ++i)
        transfers.push_back(std::thread(transfer, &account, i));

    for (int i=0; i<100; ++i)
        transfers[i].join();

    for (int i=0; i<100; ++i)
        transfers.pop_back();

    std::cout << "Correct Balance (exactly 4950): " << account.getBalance() << "\n";

    EXPECT_EQ(4950, account.getBalance());
}
