#ifndef __GRID_PRINTER_H__
#define __GRID_PRINTER_H__

#include <iostream>
#include <string>
#include "grid.h"

namespace jarduino {

class GridPrinter {
 public:
  template <typename T>
  static void Print(const Grid<T>& grid, char (*to_char_func)(const T&)) {
    using namespace std;
    for (int y = grid.Height() - 1;  y >= 0; --y) {
      for (int x = 0; x < grid.Width(); ++x) {
        cout << (*to_char_func)(*grid.Get(x, y));
      }
      cout << endl;
    }
  }

  template <typename T>
  static void Print(const Grid<T>& grid) {
    using namespace std;
    for (int y = grid.Height() - 1;  y >= 0; --y) {
      for (int x = 0; x < grid.Width(); ++x) {
        cout << ((char)(*grid.Get(x, y)));
      }
      cout << endl;
    }
  }

  template <typename T>
  static void PrintWithNumbers(const Grid<T>& grid) {
    using namespace std;
    for (int y = grid.Height() - 1;  y >= 0; --y) {
      for (int x = 0; x < grid.Width(); ++x) {
        cout << ((char)(*grid.Get(x, y)));
      }
      cout << " " << y % 10;
      cout << endl;
    }
    cout << endl;
    for (int x = 0; x < grid.Width(); ++x) {
      cout << x % 10;
    }
    cout << endl;
  }
};

}  // namespace jarduino
#endif
