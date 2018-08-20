#include <iostream>

#include "grid_printer.h"
#include "test_helpers.h"

namespace jarduino {
  char IntToLastDigit(const int& x) {
    if (x > 0) {
      return ('0' + ( x % 10));
    } else {
      return '.';
    }
  }

}  // namespace jarduino

int main ()
{
  using namespace jarduino;
  using namespace std;

  {
    cout << "2-wide 3-tall grid: Should show 3 at (1,1)" << endl;
    Grid<int> grid(2, 3);
    grid.Set(1, 1, 123);
    GridPrinter::Print(grid, IntToLastDigit);
  }
  {
    cout << "4-wide 3-tall grid: Should show 3 at (1,1), 9 at (0,1), 8 at (2,0), 7 at (3,1)" << endl;
    Grid<int> grid(4, 3);
    grid.Set(1, 1, 123);
    grid.Set(0, 1, 999);
    grid.Set(2, 0, 8);
    grid.Set(3, 1, 7);
    GridPrinter::Print(grid, IntToLastDigit);
  }

  std::cout << "Inspect results manually to determine if tests passed." << std::endl;
  return 0;
}

