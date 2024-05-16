#ifndef __DUMPER_SERIES_HH__
#define __DUMPER_SERIES_HH__
/* -------------------------------------------------------------------------- */
#include "series.hh"
#include <iomanip>
/* -------------------------------------------------------------------------- */

class DumperSeries {

public:
  DumperSeries(Series &series) : series(series){};

  virtual void dump(std::ostream &os) = 0;

  void setPrecision(UInt precision) { this->precision = precision; }
  void setMaxIter(UInt maxiter) { this->maxiter = maxiter; }

protected:
  Series &series;
  UInt precision = 4;
  UInt maxiter = 100;
};

inline std::ostream &operator<<(std::ostream &os, DumperSeries &dumper) {
  dumper.dump(os);
  return os;
}
#endif /* __DUMPER_SERIES_HH__ */
