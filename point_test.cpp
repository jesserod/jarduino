#include <iostream>

#include "point.h"
#include "test_helpers.h"

namespace jarduino {

void TestPoint() {
  {
    Point<int> p;
    EXPECT_EQ(p.X(), 0);
    EXPECT_EQ(p.Y(), 0);
  }
  {
    Point<int> p(1, 2);
    EXPECT_EQ(p.X(), 1);
    EXPECT_EQ(p.Y(), 2);
  }
  {
    Point<int> p;
    p.SetX(10);
    EXPECT_EQ(p.X(), 10);
    EXPECT_EQ(p.Y(), 0);
  }
  {
    Point<int> p;
    p.SetY(10);
    EXPECT_EQ(p.X(), 0);
    EXPECT_EQ(p.Y(), 10);
  }
  {
    Point<float> p(1.5, -2);
    EXPECT_FLOAT_EQ(p.X(), 1.5);
    EXPECT_FLOAT_EQ(p.Y(), -2);
  }
}

}  // namespace jarduino

int main()
{
  using namespace jarduino;
  TEST(TestPoint);

  std::cout << "Tests passed!" << std::endl;
  return 0;
}

