#ifndef __GRID_H__
#define __GRID_H__

#include <stdlib.h>     /* malloc, free, rand */
#include <assert.h>

namespace jarduino {

template <typename T>
class Grid {
 public:
  Grid() { Init(0, 0); }

  Grid(int h, int w) { Init(h, w); };

  void Init(int h, int w) {
    height_ = h;
    width_ = w;
    // Sanity check
    assert(h * w < 10000);
    data = (T*) calloc(h * w, sizeof(T));
  }

  ~Grid() {
    free(data);
  }

  int Width() const { return width_; }

  int Height() const { return height_; }

  T* Get(int x, int y) const {
    assert(x >= 0 && x < Width());
    assert(y >= 0 && y < Height());
    return &data[x + y * Width()];
  }

  void Set(int x, int y, const T& value) {
    *Get(x, y) = value;
  }

 private:
  int width_;
  int height_;
  T* data;
};

}  // namespace jarduino

#endif
