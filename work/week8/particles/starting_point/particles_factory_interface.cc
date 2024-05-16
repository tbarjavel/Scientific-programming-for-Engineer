#include "particles_factory_interface.hh"
#include "planets_factory.hh"
/* -------------------------------------------------------------------------- */
ParticlesFactoryInterface& ParticlesFactoryInterface::getInstance() {
	// if (factory == nullptr){
	// 	factory = new ParticlesFactoryInterface();
	// }
	// return *factory;
}

/* -------------------------------------------------------------------------- */
ParticlesFactoryInterface* ParticlesFactoryInterface::factory = nullptr;