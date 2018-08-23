#include <iostream>

#include "array.h"
#include "test_helpers.h"

namespace jarduino {

void Test1() {
  Array<int> a(1);
  EXPECT_EQ(a.Size(), 1);
  EXPECT_EQ(a.Get(0), 0);
  a.Resize(3);
  EXPECT_EQ(a.Get(0), 0);
  EXPECT_EQ(a.Get(1), 0);
  EXPECT_EQ(a.Get(2), 0);
  a.Set(1, 555);
  EXPECT_EQ(a.Get(1), 555);
  a.Resize(2);
  EXPECT_EQ(a.Get(1), 555);
  EXPECT_EQ(a.Size(), 2);
  a.Resize(10);
  EXPECT_EQ(a.Size(), 10);
  EXPECT_EQ(a.Get(1), 555);
  EXPECT_EQ(a.Get(9), 0);
  a.Init(10);
  EXPECT_EQ(a.Size(), 10);
  EXPECT_EQ(a.Get(1), 0);
  EXPECT_EQ(a.Get(9), 0);
}

}  // namespace jarduino

int main()
{
  using namespace jarduino;
  TEST(Test1);

  std::cout << "Tests passed!" << std::endl;
  return 0;
}

