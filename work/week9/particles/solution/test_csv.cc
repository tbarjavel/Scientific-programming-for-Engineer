#include <gtest/gtest.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

//#include "my_types.cc"
/*#include "compute_gravity.cc"
#include "compute_verlet_integration.cc"
#include "csv_reader.cc"
#include "csv_writer.cc"
#include "my_types.hh"
#include "planets_factory.cc"
#include "particles_factory_interface.cc"
#include "system.cc"*/


#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "my_types.hh"
#include "planets_factory.hh"
#include "particles_factory_interface.hh"
#include "system.hh"


/* -------------------------------------------------------------------------- */

/* Run command:
    cd build
    g++ ../test_csv.cc ../csv_reader.cc ../csv_writer.cc ../system.cc ../particle.cc ../planet.cc ../vector.cc -o test -lgtest_main -lgtest -lpthread -std=c++14
    ./test
*/

struct PlanetStruct {
    std::array<Real, 3> position;
    std::array<Real, 3> velocity;
    std::array<Real, 3> force;
    Real mass;
    std::string name;
};

// Fixture class
class TestCsv : public ::testing::Test {
protected:

    void SetUp() override {
        // Create planet structure with fields corresponding to csv file content
        planet_test.position = {1, 2, 3};
        planet_test.velocity = {5, 0, 6};
        planet_test.force = {-1, -1, -2};
        planet_test.mass = 10;
        planet_test.name = "test";

        // // Create new system and read planet from file
        // system = new System();
        // CsvReader reader("test_reader.csv");
        // reader.read(*system);
        std::cout << "Step0" << std::endl;
        PlanetsFactory::getInstance();
/*        ParticlesFactoryInterface& factory = ParticlesFactoryInterface::getInstance();
        SystemEvolution& evol = factory.createSimulation(filename, timestep);
*/
        // Extract explicit planet object
        // planet = dynamic_cast<Planet*>(&system->getParticle(0));
    
        
        // // Write system into output file

        //std::string outfile = "test_writer.csv";
        // CsvWriter writer(outfile);
        // writer.write(*system);

        // Get 1st line of output file
        // std::ifstream is(outfile.c_str());
        // getline(is, line);
        // is.close();
    }

    void TearDown() override {
        // Clear and delete system
        // system->removeParticle(0);
        // delete system;
        //evol.getSystem().removeParticle(0);
       //delete factory;
    }

    //std::cout << "Step1" << std::endl;
    std::string filename="test_reader.csv";
    Real nsteps=1;
    Real timestep=5e-3;
    PlanetStruct planet_test;

    // System* system;
   // std::cout << "Step2" << std::endl;
    //std::unique_ptr<SystemEvolution> system_evolution = nullptr;
    ParticlesFactoryInterface& factory = ParticlesFactoryInterface::getInstance();
    //SystemEvolution::SystemEvolution(std::unique_ptr<System> system)
    //std::cout << "Step3" << std::endl;
    SystemEvolution& evol = factory.createSimulation(filename, timestep);
    //std::cout << "Step4" << std::endl;
    Particle& planet = evol.getSystem().getParticle(0);
    //std::cout << "Step5" << std::endl;
    std::string line;
};


// Test CsvReader
TEST_F(TestCsv, reading) {
    EXPECT_EQ(planet_test.mass, planet->getMass());
    for (UInt i = 0; i < 3; ++i) {
        EXPECT_EQ(planet_test.position[i], planet->getPosition()[i]);
        EXPECT_EQ(planet_test.velocity[i], planet->getVelocity()[i]);
        EXPECT_EQ(planet_test.force[i], planet->getForce()[i]);
    }
    // EXPECT_EQ(planet_test.name, planet->getName());
std::cout << "Step6" << std::endl;
/*    EXPECT_EQ(planet_test.mass, planet.getMass());
for (UInt i = 0; i < 3; ++i) {
    std::cout << "Step7" << std::endl;
        EXPECT_EQ(planet_test.position[i], planet.getPosition()[i]);
        EXPECT_EQ(planet_test.velocity[i], planet.getVelocity()[i]);
        EXPECT_EQ(planet_test.force[i], planet.getForce()[i]);
    }*/
    // EXPECT_EQ(planet_test.name, evol.getSystem().getParticle(0).getName());


}


int main(int argc, char **argv) {
    std::cout << "StepMAIN" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    std::cout << "StepTesting" << std::endl;
    return RUN_ALL_TESTS();
}

// // Test CsvWriter
// TEST_F(TestCsv, writing) {
//     EXPECT_EQ(line, "1 2 3 5 0 6 -1 -1 -2 10 test ");
// }
