
#include <iostream>
#include <gtest/gtest.h>

// -- The Dimond problem --
// Desc:  When 2 superclasses (M, N) of a class (Z) have a common base class (A).
// Issue: The Constructor of A is called twice.
// Fix:   Make M and N virtual base classes like MM and NN are.
//        That is inherit A as: virtual public A.

namespace {

int idx;

class A
{
public:
    A() { std::cout << "Construct A\n"; idx++; }
};

class M : public A
{
public:
    M() { std::cout << "Construct M\n"; idx++; }
};

class N : public A
{
public:
    N() { std::cout << "Construct N\n"; idx++; }
};

class Z : public M, public N
{
public:
    Z() { std::cout << "Construct Z\n"; idx++; }
};

}

TEST(DiamondTests, FailedDoubleInheritanceTest)
{
    // Construct: A,M,A(again!),N,Z
    // Constructor for A class is called twice

    idx = 0;
    Z z;
    EXPECT_EQ(idx, 5);
}

namespace {

class MM : virtual public A
{
public:
    MM() { std::cout << "Construct MM\n"; idx++; }
};

class NN : virtual public A
{
public:
    NN() { std::cout << "Construct NN\n"; idx++; }
};

class ZZ : public MM, public NN
{
public:
    ZZ() { std::cout << "Construct ZZ\n"; idx++; }
};

}

TEST(DiamondTests, CorrectDoubleInheritanceTest)
{
    // Construct: A,MM,NN,ZZ
    // Constructor for A class is called once, thanks to virtual classes inheritance

    idx = 0;
    ZZ zz;
    EXPECT_EQ(idx, 4);
}
