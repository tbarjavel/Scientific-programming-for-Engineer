#include "compute_arithmetic.hh"
/* -------------------------------------------------------------------------- */

ComputeAlgebraic::ComputeAlgebraic() {
  this->func = [](UInt i) { return 1. * i; };
}

/* -------------------------------------------------------------------------- */

double ComputeAlgebraic::getAnalyticPrediction() {
  return 1. * this->current_term * (this->current_term + 1) / 2.;
}
