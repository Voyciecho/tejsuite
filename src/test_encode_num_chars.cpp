
#include <gtest/gtest.h>
#include <string>

// Run Length Encoding function
//   "aaa" returns "a3"
//   "abbcccdddd" returns "a1b2c3d4"

void encodeRLE(std::string& dst, std::string& src)
{
    int len = src.length();

    for (int i=0; i<len; ++i)
    {
        int count = 1;
        while (i<len-1 && src[i]==src[i+1])
        {
            i++;
            count++;
        }
        dst += src[i] + std::to_string(count);
    }
}

TEST(RunLengthEncodeTest, EncodeRLETest)
{
    std::string src("abbcccdddd");
    std::string dst;

    encodeRLE(dst, src);

    EXPECT_EQ(dst.compare("a1b2c3d4"), 0);
}
