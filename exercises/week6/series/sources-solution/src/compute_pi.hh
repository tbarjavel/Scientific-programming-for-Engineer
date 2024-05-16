#ifndef __COMPUTE_PI_HH__
#define __COMPUTE_PI_HH__
/* -------------------------------------------------------------------------- */
#include "series.hh"
/* -------------------------------------------------------------------------- */

class ComputePi : public Series {
public:
  ComputePi();
  double compute(UInt N) override;
  double getAnalyticPrediction() override;
};

#endif /* __COMPUTE_PI_HH__ */
