#include "2d.h"

namespace jarduino {

float ToDegrees(float radians) {
  float positive_radians = radians >= 0 ? radians : (2*PI + radians);
  return positive_radians * 180.0 / PI;
}

float ToRadians(float degrees) {
  return degrees * PI / 180.0;
}

}  // namespace jarduino
