/* -------------------------------------------------------------------------- */
#include "dumper_series.hh"
/* -------------------------------------------------------------------------- */

class PrintSeries : public DumperSeries {
public:
  PrintSeries(Series &series, UInt freq);

  void dump(std::ostream &os) override;

private:
  UInt freq = 10;
};
