#include <cmath>
#include <iostream>
/* -------------------------------------------------------------------------- */
#include "write_series.hh"
#include <algorithm>
#include <fstream>
/* -------------------------------------------------------------------------- */

WriteSeries::WriteSeries(Series &series, const std::string &delimiter)
    : DumperSeries(series), delimiter(delimiter) {}

/* -------------------------------------------------------------------------- */

void WriteSeries::dump(std::ostream &os) {

  os << std::setprecision(this->precision);
  os << std::scientific;

  for (UInt i = 1; i < this->maxiter; ++i) {
    double res = series.compute(i);
    os << i << this->delimiter;
    os << res << this->delimiter;
    os << series.getAnalyticPrediction() << std::endl;
  }
}

/* -------------------------------------------------------------------------- */

void WriteSeries::dump() {
  std::string namefile = "iterations";
  std::string extension;
  if (extensions.count(delimiter) == 0)
    extension = ".txt";
  else
    extension = extensions[delimiter];

  std::ofstream outfile(namefile + extension);
  this->dump(outfile);
}
