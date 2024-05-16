#include "series.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */

Series::Series() {}

/* -------------------------------------------------------------------------- */

double Series::compute(UInt N) {

  if (current_term <= N)
    N -= this->current_term;
  else {
    this->current_value = 0.;
    this->current_term = 0;
  }

  for (UInt k = 0; k < N; ++k) {
    ++current_term;
    current_value += func(current_term);
  }

  return current_value;
}

/* -------------------------------------------------------------------------- */
double Series::getAnalyticPrediction() { return nan(""); }
