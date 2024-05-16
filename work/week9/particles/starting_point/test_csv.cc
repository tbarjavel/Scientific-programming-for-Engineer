#include <gtest/gtest.h>
#include <cstdlib>
#include <fstream>

#include "csv_reader.hh"
#include "csv_writer.hh"
#include "my_types.hh"
#include "system.hh"
#include "planet.hh"


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

        // Create new system and read planet from file
        system = new System();
        CsvReader reader("test_reader.csv");
        reader.read(*system);

        // Extract explicit planet object
        planet = dynamic_cast<Planet*>(&system->getParticle(0));

        // Write system into output file
        std::string outfile = "test_writer.csv";
        CsvWriter writer(outfile);
        writer.write(*system);

        // Get 1st line of output file
        std::ifstream is(outfile.c_str());
        getline(is, line);
        is.close();
    }

    void TearDown() override {
        // Clear and delete system
        system->removeParticle(0);
        delete system;
    }

    PlanetStruct planet_test;
    System* system;
    Planet* planet;
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
    EXPECT_EQ(planet_test.name, planet->getName());
}

// Test CsvWriter
TEST_F(TestCsv, writing) {
    EXPECT_EQ(line, "1 2 3 5 0 6 -1 -1 -2 10 test ");
}
