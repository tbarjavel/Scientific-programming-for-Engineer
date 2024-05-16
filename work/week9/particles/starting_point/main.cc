#include <cstdlib>
#include <iostream>
#include <sstream>

#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "my_types.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"
#include "system.hh"

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
    std::unique_ptr<System> system = std::make_unique<System>();
    // auto system = std::make_unique<System>();

    // System system;
    // Init reader obj
    CsvReader reader(filename);
    // Read from file
    reader.read(*system);

    // Init writer obj (ex 1.2)
    //std::string saveFile = "saveFile.txt";

    //Init writer obj for initial step
    std::string saveFile = "Step-0000.csv";
    CsvWriter writer(saveFile);
    writer.write(*system);

    // Create all relevant interactions
    auto gravity = std::make_shared<ComputeGravity>();

    // Create integrator and add interactions
    auto integrator = std::make_shared<ComputeVerletIntegration>(timestep);
    integrator->addInteraction(gravity);

    // Create system evolution obj
    SystemEvolution sev(std::move(system));
    sev.setNSteps(nsteps);
    sev.setDumpFreq(freq);
    sev.addCompute(integrator);
    sev.evolve();

    return EXIT_SUCCESS;
}
