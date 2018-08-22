#ifndef __2D_H__
#define __2D_H__

#include <math.h>
#include "point.h"

#define PI 3.14159265

// typedef ::jarduino::Vector jarduino::Velocity;

namespace jarduino {

template <typename T>
T min(const T& a, const T& b) {
  return (a < b) ? a : b;
}

template <typename T>
T max(const T& a, const T& b) {
  return (a > b) ? a : b;
}

float ToDegrees(float radians);

float ToRadians(float degrees);

template <typename T>
T SubtractXY(const T& a, const T& b) {
  return T(a.X() - b.X(), a.Y() - b.Y());
}

template <typename T>
T AddXY(const T& a, const T& b) {
  return T(a.X() + b.X(), a.Y() + b.Y());
}

template <typename T>
T ScaleXY(const T& a, float scale) {
  return T(a.X() * scale, a.Y() * scale);
}

template <typename T>
T MultiplyXY(const T& a, const T& b) {
  return T(a.X() * b.X(), a.Y() * b.Y());
}

template <typename T>
T DivideXY(const T& a, const T& b) {
  return T(a.X() / b.X(), a.Y() / b.Y());
}

template <typename T>
float CrossXY(const T& v, const T& w) {
  return v.X()*w.Y() - v.Y()*w.X();
}

template <typename T>
float DotProduct(const T& v, const T& w) {
  return v.X()*w.X() + v.Y()*w.Y();
}


class Vector {
 public:
  Vector() { Set(0, 0); }
  Vector(float x, float y) { Set(x, y); }
  Vector(const Vector& other) { Set(other); }
  
  float X() const { return x_; }
  float Y() const { return y_; }
  
  void SetX(float new_x) { x_ = new_x; }
  void SetY(float new_y) { y_ = new_y; }
  void Set(float x, float y) {   SetX(x); SetY(y); }
  void Set(const Vector& other) { Set(other.X(), other.Y()); }

  // Returns angle in radians.
  float Angle() const { return atan2(y_, x_); }
  float Magnitude() const { return sqrt(x_ * x_ + y_ * y_); }

  void SetMagnitude(float new_Magnitude) {
    float theta_radians = Angle();
    float new_x = cos(theta_radians) * new_Magnitude;  // cos(theta) = x / r
    float new_y = sin(theta_radians) * new_Magnitude;  // sin(theta) = y / r
    Set(new_x, new_y);
  }
  
  void SetAngleRadians(float new_angle_radians) {
    float magnitude = Magnitude();
    float new_x = cos(new_angle_radians) * magnitude;  // cos(theta) = x / r
    float new_y = sin(new_angle_radians) * magnitude;  // sin(theta) = y / r
    Set(new_x, new_y);
  }

  void SetAngleDegrees(float new_angle_degrees) {
    SetAngleRadians(ToDegrees(new_angle_degrees));
  }

  bool operator==(const Vector& other) const {
    static double kEpsilon = 1e-5;
    return fabs(other.X() - X()) < kEpsilon && fabs(other.Y() - Y()) < kEpsilon;
  }
  
  bool operator!=(const Vector& other) const { return !(*this == other); }
  
 protected:
  float x_, y_;
};

typedef Vector Velocity;

class MobileThing {
 public:
  MobileThing() {}

  MobileThing(const Velocity& velocity, const PointF& pos) { velocity_ = velocity; pos_ = pos; }

  // Distance per time.  Agnostic to actual units of distance and time. 
  jarduino::Velocity Velocity() { return velocity_; }
  void SetVelocity(const jarduino::Velocity& velocity) { velocity_ = velocity; }

  PointF Pos() { return pos_; }
  void SetPos(const PointF& pos) { pos_ = pos; }

  // Updates the position based on traveling with the current velocity for
  // some period of time, which are in the same time units as velocity.
  void Move(float time) {
    pos_.SetX(Pos().X() + time * Velocity().X());
    pos_.SetY(Pos().Y() + time * Velocity().Y());
  }

 private:
  jarduino::Velocity velocity_;
  PointF pos_;
};

// Directional line from A to B.
template <typename T>
class Line {
 public:
  Line<T>() {}

  Line<T>(const Point<T>& a, const Point<T>& b) { Set(a, b); }

  Point<T> A() const { return a_; }

  Point<T> B() const { return b_; }

  void Set(const Point<T>& a, const Point<T>& b) {
    a_ = a;
    b_ = b;
  }

  bool operator==(const Line<T>& other) const {
    A() == other.A() && B() == other.B();
  }

  bool operator!=(const Line<T>& other) const { return !(*this == other); }

  template <typename T2>
  bool Intersects(const Line<T2>& other, Point<float>* at /* nullable */) const {
    // TODO
  }

 private:
  Point<T> a_;
  Point<T> b_;

  /*

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
static bool onSegment(Point p, Point q, Point r)
{
    if (q.X() <= max(p.X(), r.X()) && q.X() >= min(p.X(), r.X()) &&
        q.Y() <= max(p.Y(), r.Y()) && q.Y() >= min(p.Y(), r.Y()))
       return true;
 
    return false;
}
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
static int orientation(PointF p, PointF q, PointF r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.Y() - p.Y()) * (r.X() - q.X()) -
              (q.X() - p.X()) * (r.Y() - q.Y());
 
    if (val == 0) return 0;  // colinear
 
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
static bool doIntersect(PointF p1, PointF q1, PointF p2, PointF q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; // At p2
 
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; // at Q2
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; // at P1
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; // At q1
 
    return false; // Doesn't fall in any of the above cases
}

*/
  

};

template <typename T>
class Box {
 public:
  Box<T>() {}

  Box<T>(const Point<T>& p1, const Point<T>& p2) {Set(p1, p2); }

  Point<T> LowerLeft() const {
    float lowX = min(p1_.X(), p2_.X());
    float lowY = min(p1_.Y(), p2_.Y());
    return Point<T>(lowX, lowY);
  }

  Point<T> UpperRight() const {
    float highX = max(p1_.X(), p2_.X());
    float highY = max(p1_.Y(), p2_.Y());
    return Point<T>(highX, highY);
 }

  void Set(const Point<T>& p1, const Point<T>& p2) {
    p1_ = p1;
    p2_ = p2;
  }

  bool operator==(const Box<T>& other) const {
    LowerLeft() == other.LowerLeft() && UpperRight() == other.UpperRight();
  }

  bool operator!=(const Box<T>& other) const { return !(*this == other); }

  template <typename T2>
  bool ContainsPoint(const Point<T2>& point) const {
    return point.X() >= LowerLeft().X() &&
           point.Y() >= LowerLeft().Y() &&
           point.X() <= UpperRight().X() &&
           point.Y() <= UpperRight().Y();
  }

  template <typename T2>
  bool IntersectsLine(const Point<T2>& a, const Point<T2>& b) const {

  }

 private:
  Point<T> p1_;
  Point<T> p2_;
};

}  // namespace jarduino
#endif
