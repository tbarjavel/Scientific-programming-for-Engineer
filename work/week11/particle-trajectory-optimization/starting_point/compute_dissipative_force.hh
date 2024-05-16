#ifndef __COMPUTE_DISSIPATIVE_FORCE__HH__
#define __COMPUTE_DISSIPATIVE_FORCE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute vertical gravity
class ComputeDissipativeForce : public Compute {

  // Virtual implementation
public:
  //! Vertical gravity implementation
  ComputeDissipativeForce();
public:
  void compute(System& system) override;

  //! set the dissipative const
  void SetMu(Real mu);
  // Members
private:
  Real mu = 0.5;
};

/* -------------------------------------------------------------------------- */
#endif // __COMPUTE_DISSIPATIVE_FORCE__HH__
