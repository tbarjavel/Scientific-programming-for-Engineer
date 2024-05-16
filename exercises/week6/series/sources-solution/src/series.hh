#ifndef __SERIES_HH__
#define __SERIES_HH__
/* -------------------------------------------------------------------------- */
#include "main.hh"
#include <functional>
#include <ostream>
#include <cmath>
/* -------------------------------------------------------------------------- */

class Series {
public:
  Series();

  virtual double compute(UInt N);
  virtual double getAnalyticPrediction();

protected:
  std::function<Real(UInt)> func;
  UInt current_term = 0;
  double current_value = 0.;
};

#endif /* __SERIES_HH__ */
