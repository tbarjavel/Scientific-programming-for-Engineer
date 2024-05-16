/* -------------------------------------------------------------------------- */
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
/* -------------------------------------------------------------------------- */

int main(int argc, char ** argv){

  unsigned long maxiter = atof(argv[1]);
  float pi = 0.;
  float pi2 = 0.;

  for (unsigned long k = 1 ; k < maxiter ; ++k){
    pi += 1./(1.*k*k);

    unsigned long k2 = maxiter-k;
    pi2 += 1./(1.*k2*k2);
    

  }
  pi *= 6.;
  pi2 *= 6.;

  std::cout << std::scientific << std::setprecision(15) 
	    << pi << " " << pi2 << " " << M_PI*M_PI 
	    << " " << pi - M_PI*M_PI << " " << pi2 - M_PI*M_PI << std::endl;

  return EXIT_SUCCESS;
}



