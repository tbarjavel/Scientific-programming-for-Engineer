#include "compute_pi.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */

ComputePi::ComputePi() {
  func = [](UInt i) { return 1. / (1. * i * i); };
}

/* -------------------------------------------------------------------------- */

double ComputePi::compute(UInt N) {
  Series::compute(N);
  return sqrt(6. * current_value);
}

/* -------------------------------------------------------------------------- */

double ComputePi::getAnalyticPrediction() { return M_PI; }

/* -------------------------------------------------------------------------- */
