#include "ping_pong_ball.hh"

/* -------------------------------------------------------------------------- */
void PingPongBall::printself(std::ostream& stream) const {
	Particle::printself(stream);
	stream << " " << radius;
}

/* -------------------------------------------------------------------------- */

void PingPongBall::initself(std::istream& sstr) {
//	stream << "# x y z  vx vy vz fx fy fz mass radius" << std::endl;
	Particle::initself(sstr);
	sstr >> radius;
}
