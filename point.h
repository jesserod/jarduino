#ifndef __POINT_H__
#define __POINT_H__

namespace jarduino {

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

}  // namespace jarduino
#endif
