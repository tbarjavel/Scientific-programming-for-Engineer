#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>      // std::iota
#include <iomanip>
#include <iostream>
/* -------------------------------------------------------------------------- */

void printVec(std::vector<double> v) {
    std::cout << " v = [";
    for (auto const &e : v) {
        std::cout << e << " ";
    }
    std::cout << "]" << std::endl;
}


int main(int argc, char ** argv){

    int n = 10;
    std::cout << "Initialization: ";
    std::vector<double> v(n);
    printVec(v);

    std::cout << "Filling with zeros: ";
    std::fill(v.begin(), v.end(), 0);
    printVec(v);

    std::cout << "Filling with incremental values from 1: ";
    std::iota(v.begin(), v.end(), 1);
    printVec(v);

    auto squarer = [](double x) { return x * x; };
    double x = 10;
    std::cout << "x = " << x << ", x2 = " << squarer(x) << std::endl;

    for (auto &e : v) { e = squarer(e); }
    std::cout << "Squaring vector with range loop: ";
    printVec(v);

    std::iota(v.begin(), v.end(), 1);
    std::for_each(v.begin(), v.end(), [](auto &x) { x = x * x; });
    std::cout << "Squaring vector with for_each: ";
    printVec(v);

    // Natural squares sum formula
    int s = n  * (n + 1) * (2 * n + 1) / 6;
    std::cout << "n(n+1)(2n+1)/6 = " << s << std::endl;

    // Compute sum in different ways
    double sum = 0.;
    auto adder = [&sum] (double x) { sum += x; };
    std::for_each(v.begin(), v.end(), adder);
    std::cout << "Summing vector using for_each: s = " << sum << std::endl;
    sum = std::accumulate(v.begin(), v.end(), 0.);
    std::cout << "Summing vector with accumulate: s = " << sum << std::endl;

    // Compute Pi without loop
    std::reverse(v.begin(), v.end());  // reverse
    std::for_each(v.begin(), v.end(), [](auto &x) { x = 1. / x; });  // loop through and invert
    double pi = sqrt(6 * std::accumulate(v.begin(), v.end(), 0.));  // sum, times 6 and sqrt
    std::cout<< std::fixed << std::setprecision(20) << "Pi = " << pi << std::endl;

    return EXIT_SUCCESS;
}



