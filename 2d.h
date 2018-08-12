#ifndef __2D_H__
#define __2D_H__

#include <math.h>

#define PI 3.14159265

namespace jarduino {

float ToDegrees(float radians);

float ToRadians(float degrees);

class Vector {
 public:
  Vector() { Update(0, 0); }
  Vector(float x, float y) { Update(x, y); }
  Vector(const Vector& other) { Update(other.X(), other.Y()); }
  
  float X() const { return x_; }
  float Y() const { return y_; }
  
  float SetX(float new_x) { x_ = new_x; }
  float SetY(float new_y) { y_ = new_y; }
  void Update(float x, float y) {   SetX(x); SetY(y); }

  // Returns angle in radians.
  float Angle() const { return atan2(y_, x_); }
  float Length() const { return sqrt(x_ * x_ + y_ * y_); }

  void SetLength(float new_length) {
    float theta_radians = Angle();
    float new_x = cos(theta_radians) * new_length;  // cos(theta) = x / r
    float new_y = sin(theta_radians) * new_length;  // sin(theta) = y / r
    Update(new_x, new_y);
  }
  
  void SetAngleRadians(float new_angle_radians) {
    float length = Length();
    float new_x = cos(new_angle_radians) * length;  // cos(theta) = x / r
    float new_y = sin(new_angle_radians) * length;  // sin(theta) = y / r
    Update(new_x, new_y);
  }

  void SetAngleDegrees(float new_angle_degrees) {
    SetAngleRadians(ToDegrees(new_angle_degrees));
  }
  
 protected:
  float x_, y_;
};

class Velocity : public Vector {
 public:
  Velocity() { Update(0, 0); }
  Velocity(float x, float y) { Update(x, y); }
  Velocity(const Velocity& other) { Update(other.X(), other.Y()); }

  float Speed() const { return Length(); }

  void SetSpeed(float new_speed) {
    SetLength(new_speed);
  }
};

}  // namespace jarduino
#endif
