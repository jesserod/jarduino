#include <iostream>

#include "line_drawer.h"
#include "grid_printer.h"
#include "grid.h"
#include "test_helpers.h"
#include "point.h"
#include "array.h"

using namespace std;

namespace jarduino {

void TestExample1() {
  Grid<char> grid(10,11, '.');
  Array<PointI> line = LineDrawer::Draw(PointI(0,2), PointI(1,4)); 
  cerr << "LINE SIZE: " << line.Size() << endl;
  for (int i = 0; i < line.Size(); ++i) {
    int x = line.Get(i).X();
    int y = line.Get(i).Y();
    cerr << x << " " << y << " " << i << endl;
    grid.Set(x, y, 'X');
  }
  GridPrinter::Print(grid);
}

}  // namespace jarduino

int main()
{
  using namespace jarduino;
  TEST(TestExample1);

  std::cout << "Manually verify that tests passed" << std::endl;
  return 0;
}

