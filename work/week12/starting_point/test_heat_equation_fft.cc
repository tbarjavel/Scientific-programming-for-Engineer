#include <gtest/gtest.h>
#include <cstdlib>
#include "my_types.hh"
#include "fft.hh"
#include "compute_temperature.hh"
#include "system.hh"
#include "csv_reader.hh"
#include "material_point.hh"
#include "material_points_factory.hh"

/*****************************************************************/

void checkZero(Matrix<complex>& M) {
    // Check for element-wise near-null equality inside a complex matrix
    for (auto&& entry : index(M)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& x = std::get<2>(entry);
        ASSERT_NEAR(std::abs(x), 0, 1e-3);
    }
}

void checkStability(std::string input_filename) {

    // Get factory instance
    MaterialPointsFactory::getInstance();
    ParticlesFactoryInterface& factory = ParticlesFactoryInterface::getInstance();

    // Create system of particles
    auto system = std::make_unique<System>();

    // Parse input file to populate system
    CsvReader reader(input_filename.c_str());
    reader.read(*system);
    auto N = system->getNbParticles();

    // Create compute object
    auto ct = ComputeTemperature(*system, 1.0);

    // Compute time derivative of temperature matrix
    Matrix<complex> M_dtheta_dt = ct.computeDerivative(*system);

    // Check that time derivative is close to zero
    checkZero(M_dtheta_dt);
}


TEST(HEAT_EQ, homogeneous) { checkStability("dumps/testnull.csv"); }
TEST(HEAT_EQ, line) { checkStability("dumps/testline.csv"); }
