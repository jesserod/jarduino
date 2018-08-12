#ifndef __2D_H__
#define __2D_H__

#include <math.h>

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

template <typename T>
class Point {
 public:
  Point<T>() { Set(0, 0); }
  Point<T>(const T& x, const T& y) { Set(x, y); }
  Point<T>(const T& other) { Set(other); }
  T X() const { return x_; }
  T Y() const { return y_; }
  void SetX(const T& new_x) { x_ = new_x; }
  void SetY(const T& new_y) { y_ = new_y; }
  void Set(const T& new_x, const T& new_y) { SetX(new_x); SetY(new_y); }
  void Set(const T& other) { Set(other.X(), other.Y()); }

  bool operator==(const Point<T>& other) const {
    static double kEpsilon = 1e-5;
    return fabs(other.X() - X()) < kEpsilon && fabs(other.Y() - Y()) < kEpsilon;
  }

  bool operator!=(const Point<T>& other) const { return !(*this == other); }

 private:
  T x_;
  T y_;
};

typedef Point<float> PointF;
typedef Point<int> PointI;
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

 private:
   Point<T> p1_;
   Point<T> p2_;
};

}  // namespace jarduino
#endif
