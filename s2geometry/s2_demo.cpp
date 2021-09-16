#include <iostream>
#include "s2/s2loop.h"
#include "s2/s2text_format.h"
#include "s2/s2region_coverer.h"

using s2textformat::MakeLoopOrDie;

string tokens(const S2CellUnion &cell_union)
{
  string out;
  for (S2CellId cell_id : cell_union){
    if (!out.empty()){
      out += ",";
    }
    out += cell_id.ToToken();
  }
  return out;
}

int main()
{
  S2RegionCoverer coverer;
  coverer.mutable_options()->set_min_level(0);
  coverer.mutable_options()->set_max_level(16);
  coverer.mutable_options()->set_max_cells(100);

  auto outer = MakeLoopOrDie("-35.364:153.207, -35.364:158.207, -32.364:158.207, -32.364:153.207");
  auto cells = coverer.GetCovering(*outer);

  auto inner1 = MakeLoopOrDie("-34.364:154.207, -34.364:155.207, -33.364:155.207, -33.364:154.207");
  cells = cells.Difference(coverer.GetInteriorCovering(*inner1));

  auto inner2 = MakeLoopOrDie("-34.364:156.207, -34.364:157.207, -33.364:157.207, -33.364:156.207");
  cells = cells.Difference(coverer.GetInteriorCovering(*inner2));

  std::cout << tokens(cells) << std::endl;

  return 0;
}
