#ifndef __COMPUTE_VERTICAL_GRAVITY__HH__
#define __COMPUTE_VERTICAL_GRAVITY__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute vertical gravity
class ComputeVerticalGravity : public Compute {

  // Virtual implementation
public:
  //! Vertical gravity implementation
 ComputeVerticalGravity();
public:
  void compute(System& system) override;

  //! set the dissipative const
  void SetVg(Real vg);
  // Members
private:
  //! g constant
  Real vg = 9.81;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_GRAVITY__HH__
