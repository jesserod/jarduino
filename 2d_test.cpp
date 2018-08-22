#include <iostream>

#include "2d.h"
#include "point.h"
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
    v.Set(3, 4.5);
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

void TestVectorMagnitude() {
  EXPECT_FLOAT_EQ(Vector(0, 0).Magnitude(), 0);
  EXPECT_FLOAT_EQ(Vector(1, 0).Magnitude(), 1);
  EXPECT_FLOAT_EQ(Vector(0, 1).Magnitude(), 1);
  EXPECT_FLOAT_EQ(Vector(0, -1).Magnitude(), 1);
  EXPECT_FLOAT_EQ(Vector(-1, 0).Magnitude(), 1);
  EXPECT_FLOAT_EQ(Vector(-2, 0).Magnitude(), 2);
  EXPECT_FLOAT_EQ(Vector(-1, -1).Magnitude(), sqrt(2));
  EXPECT_FLOAT_EQ(Vector(-1, 2).Magnitude(), sqrt(1+4));
}

void TestVectorSetMagnitude() {
  {
    Vector v(1, 0);
    v.SetMagnitude(1.5);
    EXPECT_FLOAT_EQ(v.Magnitude(), 1.5);
    EXPECT_FLOAT_EQ(v.X(), 1.5);
    EXPECT_FLOAT_EQ(v.Y(), 0);
  }
  {
    Vector v(-1, 0);
    v.SetMagnitude(1.5);
    EXPECT_FLOAT_EQ(v.Magnitude(), 1.5);
    EXPECT_FLOAT_EQ(v.X(), -1.5);
    EXPECT_FLOAT_EQ(v.Y(), 0);
  }
  {
    Vector v(-1, -1);
    v.SetMagnitude(0.1);
    EXPECT_FLOAT_EQ(v.X(), -0.1 / sqrt(2));
    EXPECT_FLOAT_EQ(v.Y(), -0.1 / sqrt(2));
  }
  {
    Vector v(1, -2);
    v.SetMagnitude(2);
    EXPECT_FLOAT_EQ(v.Magnitude(), 2);
    EXPECT_FLOAT_EQ(v.X(), 0.894427);
    EXPECT_FLOAT_EQ(v.Y(), -1.78885);
  }
}


void TestMobileThing() {
  {
    MobileThing m(Velocity(1,2), PointF(10,20));
    EXPECT_OBJECT_EQ(m.Velocity(), Velocity(1,2));
    EXPECT_OBJECT_EQ(m.Pos(), PointF(10,20));
    
    m.Move(1.0);
    EXPECT_OBJECT_EQ(m.Velocity(), Velocity(1,2));
    EXPECT_OBJECT_EQ(m.Pos(), PointF(11,22));

    m.Move(0.5);
    EXPECT_OBJECT_EQ(m.Velocity(), Velocity(1,2));
    EXPECT_OBJECT_EQ(m.Pos(), PointF(11.5,23));

    m.Move(-1);
    EXPECT_OBJECT_EQ(m.Velocity(), Velocity(1,2));
    EXPECT_OBJECT_EQ(m.Pos(), PointF(10.5,21));
  }
}

void TestBoxBasic() {
  {
    Box<float> b;
    EXPECT_OBJECT_EQ(b, Box<float>(PointF(0, 0), PointF(0, 0)));
  }
  {
    Box<float> b(PointF(1,2), PointF(3, 4));
    EXPECT_OBJECT_EQ(b, Box<float>(PointF(1, 2), PointF(3, 4)));
    EXPECT_OBJECT_EQ(b, Box<float>(PointF(3, 4), PointF(1, 2)));
  }
  {
    Box<float> b(PointF(-1,-2), PointF(-3, 4));
    EXPECT_OBJECT_EQ(b, Box<float>(PointF(-1, -2), PointF(-3, 4)));
    EXPECT_OBJECT_EQ(b, Box<float>(PointF(-3, 4), PointF(-1, -2)));
  }
  {
    Box<float> b(PointF(-1,-2), PointF(-3, 4));
    EXPECT_OBJECT_EQ(b.LowerLeft(), PointF(-3, -2));
    EXPECT_OBJECT_EQ(b.UpperRight(), PointF(-1, 4));
  }
}

void TestBoxContains() {
  {
    Box<float> b(PointF(1,2), PointF(4, 6));
    EXPECT_EQ(b.ContainsPoint(Point<int>(1,2)), true);
    EXPECT_EQ(b.ContainsPoint(Point<int>(4,6)), true);
    EXPECT_EQ(b.ContainsPoint(Point<int>(1,6)), true);
    EXPECT_EQ(b.ContainsPoint(Point<int>(4,2)), true);
    EXPECT_EQ(b.ContainsPoint(Point<int>(1,3)), true);
    EXPECT_EQ(b.ContainsPoint(Point<int>(2,3)), true);
    EXPECT_EQ(b.ContainsPoint(Point<int>(-2,3)), false);
    EXPECT_EQ(b.ContainsPoint(Point<int>(2,-3)), false);
    EXPECT_EQ(b.ContainsPoint(Point<int>(-2,-3)), false);

    EXPECT_EQ(b.ContainsPoint(Point<float>(1, 6)), true);
    EXPECT_EQ(b.ContainsPoint(Point<float>(1.01, 5.99)), true);
    EXPECT_EQ(b.ContainsPoint(Point<float>(0.99, 5.99)), false);
    EXPECT_EQ(b.ContainsPoint(Point<float>(1.5, 6.01)), false);
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
    TEST(TestVectorMagnitude);
    TEST(TestVectorSetMagnitude);
    TEST(TestMobileThing);
    TEST(TestBoxBasic);
    TEST(TestBoxContains);
  }

  std::cout << "Tests passed!" << std::endl;
  return 0;
}
