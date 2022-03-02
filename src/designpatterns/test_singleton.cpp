
#include <iostream>
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
    int m_id;
};

Singleton* Singleton::m_singleton = nullptr;

Singleton* Singleton::getInstance(int id)
{
    if (m_singleton == nullptr)
        m_singleton = new Singleton(id);

    return m_singleton;
}

TEST(SingletonTests, SimpleSingletonTest)
{
    EXPECT_EQ(Singleton::getInstance(1)->getId(), Singleton::getInstance(2)->getId());
}
