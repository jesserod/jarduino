#ifndef __LINE_DRAWER_H__
#define __LINE_DRAWER_H__

#include <string>
#include "point.h"
#include "array.h"

namespace jarduino {

class LineDrawer {
 public:
  // Returns array of points that should be displayed
  // as being a part of this line.
  static Array<PointI> Draw(const PointI& start, const PointI& end);
};

}  // namespace jarduino
#endif
