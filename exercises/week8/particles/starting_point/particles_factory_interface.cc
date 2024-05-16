#include "particles_factory_interface.hh"
#include "planets_factory.hh"
/* -------------------------------------------------------------------------- */
ParticlesFactoryInterface& ParticlesFactoryInterface::getInstance() {
}

/* -------------------------------------------------------------------------- */
ParticlesFactoryInterface* ParticlesFactoryInterface::factory = nullptr;
