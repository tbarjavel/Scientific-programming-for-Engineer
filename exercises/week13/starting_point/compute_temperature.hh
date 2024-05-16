#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute heat equation evolution
class ComputeTemperature : public Compute {

  // Virtual implementation
public:
  //! Temperature computation
  void compute(System& system) override;

};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
