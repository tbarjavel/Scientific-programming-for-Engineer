#ifndef __COMPUTE_TEMPERATURE_FINITE_DIFFERENCES__HH__
#define __COMPUTE_TEMPERATURE_FINITE_DIFFERENCES__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute heat equation evolution
class ComputeTemperatureFiniteDifferences : public Compute {

  // Virtual implementation
public:
  //! Temperature computation
  void compute(System& system) override;

  Matrix<complex> computeDerivative(System& system);

  void compute(System& system) override;

  // Time step
  Real dt;

  // System dimensions (number of particles and matrix size)
  UInt N;
  UInt sqrtN;

  // Space dimensions
  Real L = 2;  // dimension over space domain
  Real norm;  // normalization factor

  // Physical parameters (for gold)
  Real pho = 19.32;  // g/cm^3
  Real C = 0.129;  // J/g*°C

  // Laplacian of Fourier domain frequencies
  Matrix<Real> M_laplacian_q;

  // Heat rate matrix
  Matrix<Real> M_hr;

  // Fourier transform of heat distribution
  Matrix<complex> M_hv_hat;

  // temperature matrix
  Matrix<complex> M_theta;

};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE_FINITE_DIFFERENCES__HH__
