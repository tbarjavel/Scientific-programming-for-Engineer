#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "my_types.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"
#include "system.hh"
/* -------------------------------------------------------------------------- */
#include <cstdlib>
#include <iostream>
#include <sstream>
/* -------------------------------------------------------------------------- */

int main(int argc, char** argv) {
  if (argc != 6) {
    std::cout << "Usage: " << argv[0]
              << " nsteps dump_freq input.csv particle_type timestep"
              << std::endl;
    std::cout << "\tparticle type can be: planet, ping_pong" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
