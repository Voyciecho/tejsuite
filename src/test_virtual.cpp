
#include <iostream>
#include <gtest/gtest.h>

class Base
{
public:
    std::string simpleGet()
    {
        return std::string("Base");
    }
    virtual std::string get()
    {
        return std::string("Base");
    }
};

class Derived : public Base
{
public:
    std::string simpleGet()
    {
        return std::string("Derived");
    }
    std::string get() override
    {
        return std::string("Derived");
    }
};

TEST(Tests, VirtualFuncTest)
{
    // Base obj
    Base b;
    Base* b_ptr = &b;

    EXPECT_EQ(b.simpleGet().compare(std::string("Base")), 0);               // non-virtual -> Base method
    EXPECT_EQ(b.get().compare(std::string("Base")), 0);                     // non-virtual -> Base method
    EXPECT_EQ(b_ptr->simpleGet().compare(std::string("Base")), 0);          // non-virtual -> Base method
    EXPECT_EQ(b_ptr->get().compare(std::string("Base")), 0);                // non-virtual -> Base method

    // Derived obj
    Derived d;
    Derived* d_ptr = &d;

    EXPECT_EQ(d.simpleGet().compare(std::string("Derived")), 0);            // non-virtual -> Derived method -> Derived method overriding the Base method
    EXPECT_EQ(d.get().compare(std::string("Derived")), 0);                  // non-virtual -> Derived method -> Derived method overriding the Base method
    EXPECT_EQ(d_ptr->simpleGet().compare(std::string("Derived")), 0);       // non-virtual -> Derived method -> Derived method overriding the Base method
    EXPECT_EQ(d_ptr->get().compare(std::string("Derived")), 0);             // non-virtual -> Derived method -> Derived method overriding the Base method

    // Ptr to Base holding a Derived obj
    Base* d2base_ptr = &d;
    EXPECT_EQ(d2base_ptr->simpleGet().compare(std::string("Base")), 0);     // non-virtual -> early binding -> Base method
    EXPECT_EQ(d2base_ptr->get().compare(std::string("Derived")), 0);        // virtual     -> Base::getVirt() is virtual + it's overridden by Derived::getVirt() -> Derived method
}
