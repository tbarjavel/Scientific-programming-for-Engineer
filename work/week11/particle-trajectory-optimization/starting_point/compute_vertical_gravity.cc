#include "compute_vertical_gravity.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */
ComputeVerticalGravity::ComputeVerticalGravity()
{}

void ComputeVerticalGravity::compute(System& system) {
  Vector Z(std::array<Real,Vector::dim>{0,0,-1});
  for (auto & particle : system){
   // auto force=
   // std::cout<<particle.getForce()<< std::endl;
    //std::cout<<particle.getMass()<< std::endl;

    particle.getForce() += Z*particle.getMass()*(this->vg);
    }

}

/* -------------------------------------------------------------------------- */
void ComputeVerticalGravity::SetVg(Real vg) { this->vg = 9.81; }
