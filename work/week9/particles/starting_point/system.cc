#include "system.hh"

Particle& System::getParticle(UInt i) {
    return *list_particles.at(i);
}

/* -------------------------------------------------------------------------- */

void System::addParticle(const std::shared_ptr<Particle>& new_particle) {
    list_particles.push_back(new_particle);
}

void System::removeParticle(UInt particle) {
    list_particles.erase(list_particles.begin() + particle);
}

/* -------------------------------------------------------------------------- */

UInt System::getNbParticles() {
    return list_particles.size();
}
