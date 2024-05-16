#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

void print_vector(std::vector<double>& v) {
  for (double x : v)
    std::cout << x << " ";
  std::cout << std::endl;
}

int main() {
  unsigned int n = 20; // size of vector
  
  std::vector<double> values(n); // create vector with n numbers

  // Filling with zeros
  std::fill(values.begin(), values.end(), 0);
  print_vector(values);

  // Applying std::iota
  std::iota(values.begin(), values.end(), 1);
  print_vector(values); // should print "1 2 3 4 5 ..."

  // Squaring a value
  auto square_it = [](double & x) { x *= x; };
  double y = 3.;
  square_it(y);
  std::cout << "3*3 = " << y << std::endl; // should print 9.

  // Squaring values of the vector
  for (double & y : values)
    square_it(y);
  print_vector(values); // should print "1 4 9 16 25 ..."


  // [resetting values]
  std::iota(values.begin(), values.end(), 1);

  // Squaring values using std::for_each
  std::for_each(values.begin(), values.end(), square_it);
  print_vector(values); // should print "1 4 9 16 25 ..."

  // Summing the squares
  double answer = n*(n+1)*(2*n+1)/6.;
  double result = 0; // will contain the result
  // capture the result variable by-reference
  auto summation = [&result] (double & x) { result += x; };
  // apply the summation function
  std::for_each(values.begin(), values.end(), summation);
  std::cout << result << " = " << answer << std::endl;

  // Do the same with std::reduce
  result = std::accumulate(values.begin(), values.end(), 0.);
  std::cout << result << " = " << answer << std::endl;

  // We need to invert the squares
  auto inverse = [](double & x) { x = 1. / x; };
  std::for_each(values.begin(), values.end(), inverse); // apply inverse

  // Sum all squares in reverse order to avoid roundoff errors
  result = std::accumulate(values.rbegin(), values.rend(), 0.);
  double pi_estimate = std::sqrt(6. * result);
  std::cout << pi_estimate << " ~ " << M_PI << std::endl;

  return 0;
}
