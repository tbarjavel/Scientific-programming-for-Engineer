#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute contact interaction between ping-pong balls
class ComputeTemperature : public Compute {
  
public:
  //! temperature evolution implementation
  void compute(System& system) override;

  //! return the heat conductivity
  Real & getConductivity(){return conductivity;};
  //! return the heat capacity
  Real & getCapacity(){return capacity;};
  //! return the heat capacity
  Real & getDensity(){return density;};
  //! return the characteristic length of the square
  Real & getL(){return L;};
  //! return the characteristic length of the square
  Real & getDeltat(){return delta_t;};

  //! return the heat conductivity
  void setConductivity(Real conductivity){ this->conductivity = conductivity;};
  //! return the heat capacity
  void setCapacity(Real capacity){ this->capacity = capacity;};
  //! return the heat capacity
  void setDensity(Real density){ this->density = density;};
  //! return the characteristic length of the square
  void setL(Real L){ this->L = L;};
  //! return the characteristic length of the square
  void setDeltat(Real delta_t){ this->delta_t = delta_t;};

  bool implicit = true;
private:
  
  Real conductivity;
  Real capacity;
  Real density;
  //! side length of the problem
  Real L;

  Real delta_t;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
