#include "compute_verlet_integration.hh"

ComputeVerletIntegration::ComputeVerletIntegration(Real dt) : dt(dt) {}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::setDeltaT(Real dt) {
}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::compute(System& system) {
}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::addInteraction(
    std::shared_ptr<ComputeInteraction> interaction) {
}
