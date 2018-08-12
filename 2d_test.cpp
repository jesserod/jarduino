#include <iostream>
#include <math.h>       /* atan2 */
#include <assert.h>

#include "2d.h"
#include "test_helpers.h"

#define PI 3.14159265


namespace jarduino {

void TestToDegrees() {
  EXPECT_FLOAT_EQ(ToDegrees(PI/4), 45);
  EXPECT_FLOAT_EQ(ToDegrees(PI/2), 90);
  EXPECT_FLOAT_EQ(ToDegrees(2 * PI + PI/2), 360 + 90);
  EXPECT_FLOAT_EQ(ToDegrees(-PI/4), 360 - 45);
  EXPECT_FLOAT_EQ(ToDegrees(-PI/2), 360 - 90);
}

void TestToRadians() {
  EXPECT_FLOAT_EQ(PI/4, ToRadians(45));
  EXPECT_FLOAT_EQ(PI/2, ToRadians(90));
  EXPECT_FLOAT_EQ(2*PI-PI/4, ToRadians(360 - 45));
  EXPECT_FLOAT_EQ(2*PI-PI/2, ToRadians(360 - 90));
  EXPECT_FLOAT_EQ(2*PI+PI/4, ToRadians(360 + 45));
}

void TestVectorBasic() {
  {
    Vector v(1.5, 2);
    EXPECT_EQ(v.X(), 1.5);
    EXPECT_EQ(v.Y(), 2);
  }
  {
    Vector v;
    EXPECT_EQ(v.X(), 0);
    EXPECT_EQ(v.Y(), 0);
    v.SetX(1);
    EXPECT_EQ(v.X(), 1);
    v.SetY(2);
    EXPECT_EQ(v.Y(), 2);
    v.Update(3, 4.5);
    EXPECT_EQ(v.X(), 3);
    EXPECT_FLOAT_EQ(v.Y(), 4.5);
  }
}


void TestVectorAngle() {
  EXPECT_FLOAT_EQ(ToDegrees(Vector(0, 0).Angle()), 0);
  EXPECT_FLOAT_EQ(ToDegrees(Vector(1, 0).Angle()), 0);
  EXPECT_FLOAT_EQ(ToDegrees(Vector(1, 1).Angle()), 45);
  EXPECT_FLOAT_EQ(ToDegrees(Vector(0, 1).Angle()), 90);
  EXPECT_FLOAT_EQ(ToDegrees(Vector(-1, 1).Angle()), 135);
  EXPECT_FLOAT_EQ(ToDegrees(Vector(-1, 0).Angle()), 180);
  EXPECT_FLOAT_EQ(ToDegrees(Vector(-1, -1).Angle()), 225);
  EXPECT_FLOAT_EQ(ToDegrees(Vector(0, -1).Angle()), 270);
}

void TestVectorSetAngleRadians() {
  {
    Vector v(1, 0);
    v.SetAngleRadians(ToRadians(45));
    EXPECT_FLOAT_EQ(v.X(), 1 / sqrt(2));
    EXPECT_FLOAT_EQ(v.Y(), 1 / sqrt(2));
  }
  {
    Vector v(2, 0);
    v.SetAngleRadians(ToRadians(45));
    EXPECT_FLOAT_EQ(v.X(), 2 / sqrt(2));
    EXPECT_FLOAT_EQ(v.Y(), 2 / sqrt(2));
  }
  {
    Vector v(1, 1);
    v.SetAngleRadians(ToRadians(90));
    EXPECT_FLOAT_EQ(v.X(), 0);
    EXPECT_FLOAT_EQ(v.Y(), sqrt(2));
  }
  {
    Vector v(1, 1);
    v.SetAngleRadians(ToRadians(270));
    EXPECT_FLOAT_EQ(v.X(), 0);
    EXPECT_FLOAT_EQ(v.Y(), -sqrt(2));
  }
  {
    Vector v(1, 1);
    v.SetAngleRadians(ToRadians(180));
    EXPECT_FLOAT_EQ(v.X(), -sqrt(2));
    EXPECT_FLOAT_EQ(v.Y(), 0);
  }
  {
    Vector v(-1, -1);
    v.SetAngleRadians(ToRadians(45));
    EXPECT_FLOAT_EQ(v.X(), 1);
    EXPECT_FLOAT_EQ(v.Y(), 1);
  }
  {
    Vector v(1, 1);
    v.SetAngleRadians(ToRadians(360 - 90 - 45));
    EXPECT_FLOAT_EQ(v.X(), -1);
    EXPECT_FLOAT_EQ(v.Y(), -1);
  }
}

void TestVectorLength() {
  EXPECT_FLOAT_EQ(Vector(0, 0).Length(), 0);
  EXPECT_FLOAT_EQ(Vector(1, 0).Length(), 1);
  EXPECT_FLOAT_EQ(Vector(0, 1).Length(), 1);
  EXPECT_FLOAT_EQ(Vector(0, -1).Length(), 1);
  EXPECT_FLOAT_EQ(Vector(-1, 0).Length(), 1);
  EXPECT_FLOAT_EQ(Vector(-2, 0).Length(), 2);
  EXPECT_FLOAT_EQ(Vector(-1, -1).Length(), sqrt(2));
  EXPECT_FLOAT_EQ(Vector(-1, 2).Length(), sqrt(1+4));
}

void TestVectorSetLength() {
  {
    Vector v(1, 0);
    v.SetLength(1.5);
    EXPECT_FLOAT_EQ(v.Length(), 1.5);
    EXPECT_FLOAT_EQ(v.X(), 1.5);
    EXPECT_FLOAT_EQ(v.Y(), 0);
  }
  {
    Vector v(-1, 0);
    v.SetLength(1.5);
    EXPECT_FLOAT_EQ(v.Length(), 1.5);
    EXPECT_FLOAT_EQ(v.X(), -1.5);
    EXPECT_FLOAT_EQ(v.Y(), 0);
  }
  {
    Vector v(-1, -1);
    v.SetLength(0.1);
    EXPECT_FLOAT_EQ(v.X(), -0.1 / sqrt(2));
    EXPECT_FLOAT_EQ(v.Y(), -0.1 / sqrt(2));
  }
  {
    Vector v(1, -2);
    v.SetLength(2);
    EXPECT_FLOAT_EQ(v.Length(), 2);
    EXPECT_FLOAT_EQ(v.X(), 0.894427);
    EXPECT_FLOAT_EQ(v.Y(), -1.78885);
  }
}

}  // namespace jarduino


int main ()
{
  {
    using namespace jarduino;
    TEST(TestToDegrees);
    TEST(TestToRadians);
    TEST(TestVectorBasic);
    TEST(TestVectorAngle);
    TEST(TestVectorSetAngleRadians);
    TEST(TestVectorLength);
    TEST(TestVectorSetLength);
  }

  std::cout << "Tests passed!" << std::endl;
  return 0;
}
