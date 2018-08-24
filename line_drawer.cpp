#include "line_drawer.h"

namespace jarduino {

namespace {
  float Abs(float value) {
    if (value < 0) {
      value *= -1;
    }
    return value;
  }

  float Max(float a, float b) {
    return a > b ? a : b;
  }

  float Ceil(float x) {
    return float(int(x + 0.5));
  }
}

Array<PointI> LineDrawer::Draw(const PointI& start, const PointI& end) {
  int x1 = start.X();
  int x2 = end.X();
  int y1 = start.Y();
  int y2 = end.Y();
  float dx = x2 - x1;
  float dy = y2 - y1;
  int steps = Max(Abs(dx), Abs(dy));
  dx /= float(steps);
  dy /= float(steps);
  float x = x1;
  float y = y1;
  Array<PointI> points(steps + 1);  // Allocate extra memory to start.
  points.Resize(steps);
  for (int i = 0; i < steps; ++i) {
    points.Get(i).Set(Ceil(x), Ceil(y));
    x += dx;
    y += dy;
  }

  // Fill in last point if it wasn't already included
  if (points.Size() == 0) {
    points.Resize(1);
    points.Get(0).Set(end.X(), end.Y());
  } else {
    PointI& last = points.Get(points.Size() - 1);
    if (last.X() != end.X() || last.Y() != end.Y()) {
      points.Resize(points.Size() + 1);
      points.Get(points.Size()-1).Set(end.X(), end.Y());
    }
  }

  return points;
}

}  // namespace jarduino
