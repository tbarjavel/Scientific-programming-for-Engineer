
#include <cmath>
#include "compute_temperature_boundaries.hh"
#include "fft.hh"
#include "material_point.hh"
/* -------------------------------------------------------------------------- */
ComputeTemperatureBoundaries::ComputeTemperatureBoundaries() { }
/* -------------------------------------------------------------------------- */

void ComputeTemperatureBoundaries::compute(System& system) {

  // Get the number of material points
  UInt N = system.getNbParticles();
  UInt sqrtN = sqrt(N);

  // Create dummy matrix object to get index functionality
  Matrix<complex> M(sqrt(N));

  // Loop through matrix coordinates
  for (auto&& entry : index(M)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);

    // Set null temperature if point is at the domain boundaries
    if ((i == 0 ) || (j == 0 ) || (i == sqrtN - 1) || (j == sqrtN - 1)) {
      Particle& par = system.getParticle(i * sqrtN + j);
      auto& mp = static_cast<MaterialPoint&>(par);
      mp.getTemperature() = 0;
    }
  }

}

/* -------------------------------------------------------------------------- */
