#include "compute_verlet_integration.hh"

ComputeVerletIntegration::ComputeVerletIntegration(Real dt) : dt(dt) {}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::setDeltaT(Real dt) {
    this->dt = dt;
}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::compute(System& system) {
    // Perfom Verlet integration for all the particles
    for (UInt i = 0; i < system.getNbParticles(); i++){
        // Get particle
        Particle& ptc = system.getParticle(i);

        // Update values
        ptc.getVelocity() += this->dt * ptc.getForce() / (2. * ptc.getMass());
        ptc.getPosition() += this->dt * ptc.getVelocity();

        // Compute forces TO IMPLEMENT

        ptc.getVelocity() += this->dt * ptc.getForce() / (2. * ptc.getMass());
    }

    // Set first particle to position and velocity = {0,0,0} to simulate the sun
    system.getParticle(0).getVelocity() = 0.0;
    system.getParticle(0).getPosition() = 0.0;
}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::addInteraction(
    std::shared_ptr<ComputeInteraction> interaction) {
}
