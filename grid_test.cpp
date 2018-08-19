#include <iostream>
#include <assert.h>

#include "grid.h"
#include "test_helpers.h"

namespace jarduino {

void Test1() {
  // EXPECT_FLOAT_EQ(ToDegrees(-PI/2), 360 - 90);
}

}  // namespace jarduino


int main ()
{
  {
    using namespace jarduino;
    TEST(Test1);
  }

  std::cout << "Tests passed!" << std::endl;
  return 0;
}
