
#include <gtest/gtest.h>
#include <string>

using namespace std;

void drawCircle(std::string& circle, int radius)
{
    int diameter = 2*radius+1;

    for (int i=0; i<diameter; ++i)
    {
        for (int j=0; j<diameter; ++j)
        {
            // Make top left corner a start
            int x = i-radius;
            int y = j-radius;

            // According to Pythagorean theorem
            // In any triangle x*x + y*y = z*z
            if (x*x + y*y <= radius*radius+1 )
                circle += ".";
            else
                circle += " ";
        }
        circle += "\n";
    }
}

TEST(DrawCircleWithAsciiArtTest, DrawCircleTest)
{
    string circle;

    drawCircle(circle, 10);

    EXPECT_EQ(circle.compare(
        "         ...         \n"
        "      .........      \n"
        "    .............    \n"
        "   ...............   \n"
        "  .................  \n"
        "  .................  \n"
        " ................... \n"
        " ................... \n"
        " ................... \n"
        ".....................\n"
        ".....................\n"
        ".....................\n"
        " ................... \n"
        " ................... \n"
        " ................... \n"
        "  .................  \n"
        "  .................  \n"
        "   ...............   \n"
        "    .............    \n"
        "      .........      \n"
        "         ...         \n"), 0);
}
