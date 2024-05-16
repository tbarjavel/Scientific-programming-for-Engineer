#include "compute_gravity.hh"
#include "compute_boundary.hh"
#include "compute_vertical_gravity.hh"
#include "compute_dissipative_force.hh"
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


  // the number of steps to perform
  Real nsteps;
  std::stringstream(argv[1]) >> nsteps;
  // freq to dump
  int freq;
  std::stringstream(argv[2]) >> freq;
  // init file
  std::string filename = argv[3];
  // particle type
  std::string type = argv[4];
  // timestep
  Real timestep;
  std::stringstream(argv[5]) >> timestep;

  if (type == "planet")
    PlanetsFactory::getInstance();
  else if (type == "ping_pong")
    PingPongBallsFactory::getInstance();
  else {
    std::cout << "Unknown particle type: " << type << std::endl;
    std::exit(EXIT_FAILURE);
  }

  ParticlesFactoryInterface& factory = ParticlesFactoryInterface::getInstance();

  SystemEvolution& evol = factory.createSimulation(filename, timestep);
  if (type == "ping_pong"){
    const Vector xmin(std::array<Real,Vector::dim>{0,0,0});
    const Vector xmax(std::array<Real,Vector::dim>{100,100,100});
    const Vector test(std::array<Real,Vector::dim>{1,1,-1});
    // std::cout << (test<xmin) << std::endl;
    auto boundary = std::make_shared<ComputeBoundary>(xmin, xmax);
    auto vertical_gravity= std::make_shared<ComputeVerticalGravity>();
    auto dissipative= std::make_shared<ComputeDissipativeForce>();

    evol.addCompute(boundary);
    evol.addCompute(vertical_gravity);
    evol.addCompute(dissipative);
  

  }

  evol.setNSteps(nsteps);
  evol.setDumpFreq(freq);

  evol.evolve();


  return EXIT_SUCCESS;
}
