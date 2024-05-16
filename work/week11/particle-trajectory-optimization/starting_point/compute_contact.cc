#include "compute_contact.hh"
#include "ping_pong_ball.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */
void ComputeContact::setPenalty(Real penalty) {
    this->penalty = penalty;
}
/* -------------------------------------------------------------------------- */
void ComputeContact::computePairInteraction(Particle& par1, Particle& par2) {
    
    
    PingPongBall& p1 = static_cast<PingPongBall&> (par1);
    PingPongBall& p2 = static_cast<PingPongBall&> (par2);

    p2.getForce() = 0;
    p1.getForce() = 0;

    auto v_r = p2.getPosition() - p1.getPosition();
    auto r2 = v_r.squaredNorm();

    if (r2 == 0.){
        return;
    }

    // compute the distance
    auto r = sqrt(r2);
    v_r *= 1 / r;

    Real p = 0;
    if (r < p1.getRadius() + p2.getRadius()){
        p = p1.getRadius() + p2.getRadius() - r;
    }
    // compute the pair force
    // std::cout << "Diff pos:" << v_r[0] << " " << v_r[1] << " " << v_r[2] << "; P vect: " << p << std::endl;
    auto force = v_r * this->penalty * p;

    // add up the force for both concerned particles
    p2.getForce() -= force;
    p1.getForce() += force;
}
