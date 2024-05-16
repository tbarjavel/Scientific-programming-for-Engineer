#include "compute_gravity.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */
void ComputeGravity::compute(System& system) {

  UInt size = system.getNbParticles();
  // first of all reset forces to zero
  for (auto & particle : system)
    particle.getForce() = 0;

  // the force vector
  Vector force;
  // the distance vector
  Vector v_r;
  // the normalized vector
  Vector v_nr;
  // the square of the distance
  Real r2 = 0.;
  // the distance
  Real r = 0.;

  for (UInt p1 = 0; p1 < size; ++p1) {
    Particle& par1 = system.getParticle(p1);
    for (UInt p2 = p1 + 1; p2 < size; ++p2) {
      Particle& par2 = system.getParticle(p2);

      // compute the distance vector and the square of distance

      v_r = par2.getPosition() - par1.getPosition();
      r2 = v_r.squaredNorm();

      if (r2 == 0.)
        continue;
      // compute the distance
      r = sqrt(r2);
      v_nr = v_r / r;

      // compute the pair force
      force = par1.getMass() * par2.getMass() * G / r2 * v_nr;

      // add up the force for both concerned particles
      par2.getForce() -= force;
      par1.getForce() += force;
    }
  }

}
