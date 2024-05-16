/* -------------------------------------------------------------------------- */
#include "dumper_series.hh"
#include <map>
/* -------------------------------------------------------------------------- */

class WriteSeries : public DumperSeries {
public:
  WriteSeries(Series &series, const std::string &delimiter);
  void dump(std::ostream &os) override;
  void dump();

private:
  std::string delimiter = ",";
  std::map<std::string, std::string> extensions{
      {",", ".csv"}, {"|", ".psv"}, {" ", ".txt"}};
};
