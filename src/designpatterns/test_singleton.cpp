
#include <iostream>
#include <gtest/gtest.h>

class Singleton
{
public:
    static Singleton* getInstance();

private:
    Singleton() {}
    static Singleton* m_singleton;
};

Singleton* Singleton::m_singleton = nullptr;

Singleton* Singleton::getInstance()
{
    if (m_singleton == nullptr)
        m_singleton = new Singleton();

    return m_singleton;
}

TEST(SingletonTests, SimpleSingletonTest)
{
    Singleton* s_ptr = Singleton::getInstance();
    Singleton* ss_ptr = Singleton::getInstance();

    EXPECT_EQ(s_ptr, ss_ptr);
}
