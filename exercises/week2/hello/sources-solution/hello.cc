#include "series.hh"
#include <cstdlib>
#include <iostream>
/* -------------------------------------------------------------------------- */

int main(int argc, char **charv) {

  int N = atoi(charv[1]);
  int res = computeSeries(N);

  std::cout << "Hello " << N << " res " << res << std::endl;

  return EXIT_SUCCESS;
}
