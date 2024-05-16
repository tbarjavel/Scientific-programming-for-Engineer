#include <iostream>
#include "compute_arithmetic.hh"

// Get name of the implemented serie
std::string ComputeArithmetic::getName() {
    return "ComputeArithmetic";
}

double ComputeArithmetic::getSumFromSeries(double s) {
    return s;
}

double ComputeArithmetic::getSumIncrement(unsigned int k) {
    return k;
}

double ComputeArithmetic::getSeriesFromSum(double s) {
    return s;
}
