#ifndef __COMPUTE_ALGEBRAIC_HH__
#define __COMPUTE_ALGEBRAIC_HH__
/* -------------------------------------------------------------------------- */
#include "series.hh"
/* -------------------------------------------------------------------------- */

class ComputeAlgebraic : public Series {
public:
  ComputeAlgebraic();
  double getAnalyticPrediction() override;
};

#endif /* __COMPUTE_ALGEBRAIC_HH__ */
