#ifndef __COMPUTE_GRAVITY__HH__
#define __COMPUTE_GRAVITY__HH__

/* -------------------------------------------------------------------------- */
#include "compute_interaction.hh"

//! Compute Newton gravity interaction
class ComputeGravity : public ComputeInteraction {

  // Virtual implementation
public:
  //! Newton gravity implementation
  void computePairInteraction(Particle& par1, Particle& par2) override;

  // Accessors
public:
  //! set the gravitational constant
  void setG(Real G);

  // Members
private:
  //! newton constant

  Real G = 8.8872e-10;


/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_GRAVITY__HH__
