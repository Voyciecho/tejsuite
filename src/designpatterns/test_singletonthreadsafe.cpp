
#include <iostream>
#include <thread>
#include <mutex>
#include <gtest/gtest.h>

class Singleton
{
public:
    static Singleton* getInstance(int id);
    int getId() { return m_id; }

    // Delete copy constructor
    Singleton(Singleton& X) = delete;

    // Delete assign operator
    void operator=(Singleton&) = delete;

private:
    Singleton(int id) : m_id(id) {}
    static Singleton* m_singleton;
    static std::mutex m_mtx;
    int m_id;
};

Singleton* Singleton::m_singleton = nullptr;
std::mutex Singleton::m_mtx;

Singleton* Singleton::getInstance(int id)
{
    std::lock_guard<std::mutex> lock(m_mtx);

    if (m_singleton == nullptr)
        m_singleton = new Singleton(id);

    return m_singleton;
}

std::array<int, 10> ids;

void checkInstance(int id)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* ptr = Singleton::getInstance(id);
    ids[id] = ptr->getId();
}

TEST(SingletonThreadSafeTests, MultithreadSingletonTest)
{
    std::thread threads[10];

    for (int i=0; i<10; ++i)
        threads[i] = std::thread(checkInstance, i);

    for (auto& th : threads)
        th.join();

    int idFinal = Singleton::getInstance(-1)->getId();
    EXPECT_NE(idFinal, -1);

    std::cout << "These IDs should be all equal and >= 0\n";
    for (auto& id : ids) {
        //EXPECT_EQ(idFinal, id);
        std::cout << id << "\n";
    }
}
