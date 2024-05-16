#include <algorithm>

#include "compute_verlet_integration.hh"


ComputeVerletIntegration::ComputeVerletIntegration(Real dt) : dt(dt) {}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::setDeltaT(Real dt) {
    this->dt = dt;
}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::compute(System& system) {
    // Perfom Verlet integration for all the particles

    // Update positions and velocities of all particles
    for (UInt i = 0; i < system.getNbParticles(); i++){
        Particle& ptc = system.getParticle(i);
        ptc.getVelocity() += this->dt / 2. * ptc.getForce() / ptc.getMass(); // at half time step
        ptc.getPosition() += this->dt * ptc.getVelocity();  // at full time step
    }

    // Update forces vectors from all relevant interactions
    std::for_each(interactions.begin(), interactions.end(), [&system](auto &interaction) {
        interaction->compute(system);
    });

    // Update velocities of all particles at full time step
    for (UInt i = 0; i < system.getNbParticles(); i++){
        Particle& ptc = system.getParticle(i);
        ptc.getVelocity() += this->dt / 2. * ptc.getForce() / ptc.getMass();
    }

    // Planets case: Set first particle to position and velocity = {0,0,0} to simulate the sun
    system.getParticle(0).getVelocity() = 0.0;
    system.getParticle(0).getPosition() = 0.0;
}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::addInteraction(
    std::shared_ptr<ComputeInteraction> interaction) {
    this->interactions.push_back(interaction);
}
