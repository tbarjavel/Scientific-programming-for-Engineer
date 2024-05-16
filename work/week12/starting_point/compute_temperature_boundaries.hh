#ifndef __COMPUTE_TEMPERATURE_BOUNDARIES__HH__
#define __COMPUTE_TEMPERATURE_BOUNDARIES__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
/* -------------------------------------------------------------------------- */

//! Compute interaction with simulation box
class ComputeTemperatureBoundaries : public Compute {
  // Constructors/Destructors
public:
  ComputeTemperatureBoundaries();

  // Methods
public:
  void compute(System& system) override;

};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE_BOUNDARIES__HH__
