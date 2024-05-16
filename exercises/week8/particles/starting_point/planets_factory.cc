#include "planets_factory.hh"
#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "planet.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */

std::unique_ptr<Particle> PlanetsFactory::createParticle() {
}

/* -------------------------------------------------------------------------- */

SystemEvolution& PlanetsFactory::createSimulation(const std::string& fname,
                                                  Real timestep) {
}

/* -------------------------------------------------------------------------- */

ParticlesFactoryInterface& PlanetsFactory::getInstance() {
}
/* -------------------------------------------------------------------------- */
