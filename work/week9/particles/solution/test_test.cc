#include <cmath>
#include <exception>
#include <gtest/gtest.h>

struct NegativeException : public std::exception {};

double mysqrt(double x) {

  if (x < 0.)
    throw NegativeException();

  return std::sqrt(x);
}

// MACRO function "TEST" from Google Test
// defines a test and a context
TEST(MysqrtTest, positive_integers) {
  EXPECT_EQ(2, mysqrt(4));
  EXPECT_EQ(4, mysqrt(16));
  EXPECT_EQ(3, mysqrt(9));
}