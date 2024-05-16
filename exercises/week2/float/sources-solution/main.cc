/* -------------------------------------------------------------------------- */
#include <cstdlib>
#include <cmath>
#include <iostream>
/* -------------------------------------------------------------------------- */

void exo1(){
  
  std::cout << "Exo1" << std::endl;

  int a = 0.5;
  std::cout << a << std::endl;

  double b = 1/2;
  std::cout << b << std::endl;

}
/* -------------------------------------------------------------------------- */
float tanh1(double x){
  double res = (exp(x) - exp(-x))/(exp(x) + exp(-x));
  return res;
}

float tanh2(double x){
  double res = (1 - exp(-2.*x))/(1 + exp(-2.*x));
  return res;
}


void exo2(){

  std::cout << "Exo2" << std::endl;
  
  int nstep = 10;
  double dx = 1000./nstep;
  for (int i = 0; i < nstep; ++i) {
    double a = tanh1(dx*i);
    double b = tanh2(dx*i);
    std::cout << dx*i << " " << tanh(dx*i) << " " 
	      << a << " " << b << std::endl;
  }
}
/* -------------------------------------------------------------------------- */

double tanh3(double x){
  double res = ( -2.*exp(-2.*x))/(1 + exp(-2.*x));
  return res;
}

double evolution(double pn, double v, double dt){
  return pn + dt*v;
}


void exo3(){
  
  std::cout << "Exo3.a" << std::endl;

  int nstep = 10;
  double dx = 1000./nstep;
  for (int i = 0; i < nstep; ++i) {
    double a = tanh3(dx*i);
    std::cout << dx*i << " " << tanh(dx*i) -1  << " " 
	      << a << std::endl;
  }

  std::cout << "Exo3.b" << std::endl;

  double a = 0;
  double b = a + 1e-3;
  double dt = 1e3;
  double v = 3e8;

  

  for (int i = 0; i < 40; ++i) {
    double res = b - a;
    std::cout << i << " " << res << " " << a << " " << b << std::endl; 
    a = evolution(a,v,dt);
    b = evolution(b,v,dt);
  }


}

/* -------------------------------------------------------------------------- */


int main(int argc, char ** argv){


  exo1();
  exo2();
  exo3();

  return EXIT_SUCCESS;
}



