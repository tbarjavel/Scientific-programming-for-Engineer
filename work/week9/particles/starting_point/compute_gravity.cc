#include <cmath>

#include "compute_gravity.hh"

/* -------------------------------------------------------------------------- */

void ComputeGravity::compute(System& system) {

    // Get the total number of particles
    int nparticles = system.getNbParticles();

    // Initialize types
    Vector v_ij;
    Real r2_ij = 0.;
    Real r_ij = 0;
    Vector force;
    Vector nv_ij;
         
    
        // Loop over all the particles and reset forces
    for (int pi = 0; pi < nparticles; ++pi) {
        system.getParticle(pi).getForce() = 0.;
    }

    // Loop over all the particles and gets each one's parameters
    for (int pi = 0; pi < nparticles; ++pi) {
        Particle & PI = system.getParticle(pi);
        // loop over all next interacting particles
        for (int pj = pi+1; pj < nparticles; ++pj) {
            Particle & PJ = system.getParticle(pj);

            // Gets the vector between the two particles positions
            v_ij = PJ.getPosition() - PI.getPosition();

            // Squared distance (obtained via vector class)
            r2_ij = v_ij.squaredNorm();

            // Obtained distance
            r_ij = sqrt(r2_ij);

            // Obtained corresponding normed vector
            nv_ij = v_ij / r_ij;

            // compute the gravity force vector interaction on i with j
            force = nv_ij * PI.getMass() * PJ.getMass() * G / r2_ij;

            // F_ij=-F_ji Particles have opposite forces
            PJ.getForce() -= force;
            PI.getForce() += force;
          }
    }
}
