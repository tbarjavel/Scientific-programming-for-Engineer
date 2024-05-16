#include "compute_boundary.hh"
/* -------------------------------------------------------------------------- */
ComputeBoundary::ComputeBoundary(const Vector& xmin, const Vector& xmax)
    : xmin(xmin), xmax(xmax) {
}
/* -------------------------------------------------------------------------- */

void ComputeBoundary::compute(System& system) {
	// std::cout << "Max pos: " << this->xmax[0] << " " << this->xmax[1] << " " << this->xmax[2] << std::endl;
	// std::cout << "Min pos: " << this->xmin[0] << " " << this->xmin[1] << " " << this->xmin[2] << std::endl;

    for (int i = 0; i < system.getNbParticles(); ++i){
        auto& pt = system.getParticle(i);
        // std::cout << " Pos: " << pt.getPosition()[0] << " " << pt.getPosition()[1] << " " << pt.getPosition()[2]<< "; Out MF: " << (pt.getPosition()<xmin) << std::endl;
        if (pt.getPosition() < this->xmin || pt.getPosition() > this->xmax){
        	// std::cout << "fuck it bitch" << std::endl;
            pt.getVelocity() += -2*pt.getVelocity();
        }
    }
}

/* -------------------------------------------------------------------------- */
