#include "ping_pong_balls_factory.hh"
#include "compute_contact.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "ping_pong_ball.hh"
#include <cmath>
#include <iostream>
/* -------------------------------------------------------------------------- */

std::unique_ptr<Particle> PingPongBallsFactory::createParticle() {
}

/* -------------------------------------------------------------------------- */

SystemEvolution&
PingPongBallsFactory::createSimulation(const std::string& fname,
                                       Real timestep) {
}

/* -------------------------------------------------------------------------- */

ParticlesFactoryInterface& PingPongBallsFactory::getInstance() {
}

/* -------------------------------------------------------------------------- */
