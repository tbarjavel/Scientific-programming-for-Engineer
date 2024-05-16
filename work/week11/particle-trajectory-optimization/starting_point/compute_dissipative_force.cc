#include "compute_dissipative_force.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */
ComputeDissipativeForce::ComputeDissipativeForce()
{}

void ComputeDissipativeForce::compute(System& system) {
	for (auto & particle : system){
  	//auto force = 
//    std::cout<<particle.getForce()<< std::endl;
//    std::cout<<particle.getVelocity()<< std::endl;
    particle.getForce() -= particle.getVelocity()*(this->mu);
	}

}

/* -------------------------------------------------------------------------- */
void ComputeDissipativeForce::SetMu(Real mu) { this->mu = 0.5; }

