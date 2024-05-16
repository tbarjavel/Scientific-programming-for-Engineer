#include <algorithm>
#include <cmath>
#include <exception>
#include <gtest/gtest.h>
#include <numeric>
#include <vector>

struct Particle {

  double position[3];
  double velocity[3];
  double force[3];
};

struct System {
  std::vector<Particle> particles;
};

// Fixture class
class SystemTest : public ::testing::Test {
protected:
  void SetUp() override {
    // push 10 particles
    system.particles.resize(10);
  }

  void TearDown() override {
    // clear particles
    system.particles.clear();
  }
  System system;
};

// Fixture test
TEST_F(SystemTest, IsNotEmpty) {
  // check the size of container
  EXPECT_EQ(system.particles.size(), 10);
}