#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include "series.hh"
/* -------------------------------------------------------------------------- */


int main(int argc, char ** argv) {

    // Hello N
    std::cout << "type of argc is: " << typeid(argc).name() << std::endl;
    std::cout << "type of argv is: " << typeid(argv).name() << std::endl;
    std::cout << "Number of inputs: " << argc - 1 << "\n";
    int n;
    if (argc > 1) {
        n = atoi(argv[1]);
    } else {
        n = 0;
    }
    std::cout << "Hello " << n << std::endl;

    // Print result from series (n operations necessary)
    int S = 0;
    for (int k = 1; k < n + 1; ++k) {
        S += k;
    }
    std::cout << "main: S" << n << " = " << S << "\n";

    // Print result from serie using function
    std::cout << "computeSeries: S" << n << " = " << computeSeries(n) << "\n";

    return EXIT_SUCCESS;
}
