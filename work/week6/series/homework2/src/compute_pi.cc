#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "compute_pi.hh"


double ComputePi::getAnalyticPrediction() {
    return M_PI;
}

std::string ComputePi::getName() {
    return "ComputePi";
}

double ComputePi::getSumFromSeries(double s) {
    return pow(s, 2) / 6;
}

double ComputePi::getSumIncrement(unsigned int k) {
    return 1 / pow(k, 2);
}

double ComputePi::getSeriesFromSum(double s) {
    return sqrt(6 * s);
}

