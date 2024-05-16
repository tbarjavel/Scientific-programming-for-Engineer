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

  // Parse arguments into stringstream
  std::stringstream sstr;
  for (int i = 1; i < argc; ++i) {
      // std::cout << argv[i] << std::endl;
      sstr << argv[i] << " ";
  }

  // Set number of steps
  Real nsteps;
  sstr >> nsteps;
  // Set dumper frequency
  int freq;
  sstr >> freq;
  // Set filename
  std::string filename;
  sstr >> filename;
  // std::cout << filename << std::endl;
  // Set particle's type
  std::string particle_type;
  sstr >> particle_type;
  // Set time step
  Real timestep;
  sstr >> timestep;
  // std::cout << "dt set to: " << timestep << std::endl;

  // Init system obj
  System system;
  // Init reader obj
  CsvReader reader(filename);
  // Read from file
  reader.read(system);

  // Init writer obj
  std::string saveFile = "saveFile.txt";
  CsvWriter writer(saveFile);
  writer.write(system);

  // Create integrator
  ComputeVerletIntegration integrator(timestep);
  ComputeGravity gravity;

  for (UInt i = 0; i < nsteps; ++i) {
    // Compute Verlet integration
    integrator.compute(system);
    // Compute forces
    gravity.compute(system);

    // Write updated variables at a chosen frequency
    if (fmod(i,freq)==0){
      std::string writeInterFile;
      writeInterFile = "Step" + std::to_string(i) + ".csv";
      std::cout << writeInterFile << std::endl;
      CsvWriter writer(writeInterFile);
      writer.write(system);
    }
  }

  return EXIT_SUCCESS;
}
