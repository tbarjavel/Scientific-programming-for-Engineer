/* -------------------------------------------------------------------------- */
#include <cstdlib>
#include <cmath>
#include <iostream>
/* -------------------------------------------------------------------------- */

void ex1(){
    std::cout << "EXERCISE 1" << std::endl;

    int a = 0.5;
    std::cout << a << std::endl;
    // conversion from double to int

    double a2 = 1/2;
    std::cout << a2 << std::endl;
    // Using int variables to "make it double"

    // It does not happen in python because of dynamic typing.
}


double tanhx(double x){
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

double tanhx2(double x){
    return (1 - exp(-2 * x)) / (1 + exp(-2 * x));
}

double tanhx3(double x){
    return (2 * exp(-2 * x)) / (1 + exp(-2 * x));
}

void ex2(){
    std::cout << "EXERCISE 2" << std::endl;

    double x = 10.;
    double a = exp(x);
    std::cout << "x = " << x << ", exp(x) = " << a << std::endl;

    for (double x = 0; x< 1000; x += 100){
        std::cout << "x = " << x <<
            ": tanh(x) = " << tanhx(x) <<
            ", tanhx2(x) = " << tanhx2(x) <<
            ", tanhx3(x) = " << tanhx3(x) << std::endl;
    }
}

double evolution(double pn, double v, double dt){
    return (pn + dt  *v);
}

void ex3(){
    std::cout << "EXERCISE 3" << std::endl;

    double v = 3e8;
    double p0 = 0;
    double p1 = 1e-3;
    double dt = 1000;
    for (int i = 0; i < 40; i++){
        p0 = evolution(p0, v, dt);
        p1 = evolution(p1, v, dt);
        std::cout << "Cycle " << i <<
            ": P0 = " << p0 << ", P1 = " << p1 <<
            ", distance = " << p1 - p0 << std::endl;
    }
    // Initially, p0 and p1 are very small numbers hence the computer can
    // compute their distance accurately.
    // As the photons evolve, p0 and p1 become very big, the subtraction p1 - p0
    // loses information about their smallest decimals, hence their distance
    // is approximated as zero.
}


int main(int argc, char ** argv){

    int n = 0;
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    switch (n) {
        case 0:
            ex1();
            ex2();
            ex3();
            break;
        case 1:
            ex1();
            break;
        case 2:
            ex2();
            break;
        case 3:
            ex3();
            break;
        default:
            std::cout << "Unkown exercise ID: " << n << std::endl;
    }

    return EXIT_SUCCESS;
}
