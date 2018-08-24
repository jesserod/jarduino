#include <iostream>

#include "line_drawer.h"
#include "grid_printer.h"
#include "grid.h"
#include "test_helpers.h"
#include "point.h"
#include "array.h"

using namespace std;

namespace jarduino {

namespace {

  float Abs(float value) {
    if (value < 0) {
      value *= -1;
    }
    return value;
  }

  void FillAndPrintGrid(const Array<PointI>& line, const PointI& start, const PointI& stop) {
    Grid<char> grid(20,20, '.');
    for (int i = 0; i < line.Size(); ++i) {
      int x = line.Get(i).X();
      int y = line.Get(i).Y();
      if (x == start.X() && y == start.Y()) {
        grid.Set(x, y, 'S');
      } else if (x == stop.X() && y == stop.Y()) {
        grid.Set(x, y, 'E');
      } else {
        grid.Set(x, y, 'O');
      }
    }
    GridPrinter::PrintWithNumbers(grid);
  }
}  // namespace

void TestExample1() {
  PointI start(10, 10);
  {
      PointI stop(9, 10);
      Array<PointI> line = LineDrawer::Draw(start, stop); 
      FillAndPrintGrid(line, start, stop);
      cout << endl;
      cout << endl;
  }
  {
      PointI stop(9,9);
      Array<PointI> line = LineDrawer::Draw(start, stop); 
      FillAndPrintGrid(line, start, stop);
      cout << endl;
      cout << endl;
  }
  {
      PointI stop(11,10); 
      Array<PointI> line = LineDrawer::Draw(start, stop); 
      FillAndPrintGrid(line, start, stop);
      cout << endl;
      cout << endl;
  }
  {
      PointI stop(10,11); 
      Array<PointI> line = LineDrawer::Draw(start, stop); 
      FillAndPrintGrid(line, start, stop);
      cout << endl;
      cout << endl;
  }
  {
      PointI stop(10,10); 
      Array<PointI> line = LineDrawer::Draw(start, stop); 
      FillAndPrintGrid(line, start, stop);
      cout << endl;
      cout << endl;
  }
  for (int y = 0; y < 20; ++y) {
    for (int x = 0; x < 10; ++x) {
      if ((Abs(10-x) + Abs(10-y)) < 10) {
        continue;  // Skip short lines
      }
      cerr << "Draw( (" << 10 << "," << 10 <<  ") - (" << x << "," << y << ") )" << endl;
      PointI stop(x,y);
      Array<PointI> line = LineDrawer::Draw(start, stop); 
      FillAndPrintGrid(line, start, stop);
      cout << endl;
      cout << endl;
    }
  }
}

}  // namespace jarduino

int main()
{
  using namespace jarduino;
  TEST(TestExample1);

  std::cout << "Manually verify that tests passed" << std::endl;
  return 0;
}

