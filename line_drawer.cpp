#include "line_drawer.h"

// TODO: DO NOT SUBMIT
// TODO: DO NOT SUBMIT
// TODO: DO NOT SUBMIT
#include <iostream>
using namespace std;

namespace jarduino {

namespace {
  template <typename T>
  int Sign(const T& value) {
    if (value > 0) {
      return 1;
    } else if (value < 0) {
      return -1;
    } else {
      return 0;
    }
  }

  float Abs(float value) {
    if (value < 0) {
      value *= -1;
    }
    return value;
  }
}

Array<PointI> LineDrawer::Draw(const PointI& start, const PointI& end) {
  cerr << "Draw( (" << start.X() << "," << start.Y() <<  ") - (" << end.X() << "," << end.Y() << ") )" << endl;
  int x0 = start.X();
  int x1 = end.X();
  int y0 = start.Y();
  int y1 = end.Y();
  float deltax = x1 - x0;
  float deltay = y1 - y0;

  Array<PointI> points(100);
  int x_direction = Sign(deltax);
  int y_direction = Sign(deltay);


  // Special case for vertical line:
  if (deltax == 0) {
    points.Init(Abs(deltay));
    int i = 0;
    int y = y0;
    int direction = Sign(deltay);
    for (int y = y0; y != y1; y += direction) {
      if (i >= points.Size()) {
        points.Resize(points.Size() * 2);
      }
      points.Get(i).Set(x0, y);
      i++;
    }
    return points;
  }

  if (x_direction < 0 && y_direction > 0) {
    Array<PointI> swapped_line = Draw(PointI(start.Y(), start.X()), PointI(end.Y(), end.X()));
    cerr << "swapping" << endl;
    for (int i = 0; i < swapped_line.Size(); ++i) {
      cerr << "swapping " << i << " of " << swapped_line.Size()<< endl;
      PointI& p = swapped_line.Get(i);
      int x = p.X();
      int y = p.Y();
      p.Set(y, x);
    }
    return swapped_line;
  }

  float deltaerr = Abs(deltay / deltax);   // Assume deltax != 0 (line is not vertical),
  cerr << "DELTA_X:" << deltax << endl;
  cerr << "DELTA_Y:" << deltay << endl;
  cerr << "DELTA_ERR:" << deltaerr << endl;
      // note that this division needs to be done in a way that preserves the fractional part

  float error = 0.0; // No error at start
  int i = 0;
  int y = y0;
  int x_out_of_bounds = x1 + x_direction;
  for (int x = x0; x != x_out_of_bounds; x += x_direction) {
    cerr << "here" << endl;
    if (i >= points.Size()) {
      points.Resize(points.Size() * 2);
    }
    // points.Get(i).Set(x, y);
    // i++;
    error += deltaerr;
    if (error >= 0.5) {
      y += y_direction;
      error -= 1.0;
    }
  }
  points.Get(i++).Set(x1, y1);
  points.Resize(i);  // Remove unused slots

  return points;
}

}  // namespace jarduino
