#include <iostream>

#include "line_drawer.h"
#include "test_helpers.h"

namespace jarduino {

void TestExample1() {
  EXPECT_FLOAT_EQ(1.0, 1.00000001);
}

void TestExample2() {
  EXPECT_GT(2.0, 1);
}

}  // namespace jarduino

int main()
{
  using namespace jarduino;
  TEST(TestExample1);
  TEST(TestExample2);

  std::cout << "Tests passed!" << std::endl;
  return 0;
}

