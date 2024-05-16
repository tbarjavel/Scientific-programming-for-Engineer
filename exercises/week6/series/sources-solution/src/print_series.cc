#include <cmath>
#include <iostream>
/* -------------------------------------------------------------------------- */
#include "print_series.hh"
/* -------------------------------------------------------------------------- */

PrintSeries::PrintSeries(Series &series, UInt freq)
    : DumperSeries(series), freq(freq) {}

/* -------------------------------------------------------------------------- */

void PrintSeries::dump(std::ostream &os) {
  for (UInt i = 1; i * this->freq < this->maxiter; ++i) {
    double res = series.compute(i * this->freq - 1);
    double res2 = series.compute(i * this->freq);

    os << std::setprecision(this->precision);
    os << std::scientific;

    os << i * this->freq << " " << res << " " << res2 - res;
    if (!std::isnan(series.getAnalyticPrediction())) {
      os << " " << std::abs(res2 - series.getAnalyticPrediction());
    }
    os << std::endl;
  }
}
