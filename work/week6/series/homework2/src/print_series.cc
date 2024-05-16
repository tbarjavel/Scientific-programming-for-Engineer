#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
// #include "dumper_series.hh"
#include "print_series.hh"

// Constructor
PrintSeries::PrintSeries(Series & series, unsigned int maxiter, unsigned int frequency, unsigned int precision) : DumperSeries (series) {
    this->maxiter = maxiter;
    this->frequency = frequency;
    this->precision = precision;
}

// Set numbers precision
void PrintSeries::setPrecision(unsigned int precision) {
    // std::cout.precision(precision);
    std::cout << std::setprecision(precision);
}


// Compute and display serie
void PrintSeries::dump(std::ostream & os) {
    // Display serie evolution
    os << this->series.getName() << " evolution:" << std::endl;
    for (double k = 1; k < maxiter + 1; k += frequency){
        double res = this->series.compute(k);
        os << std::defaultfloat << this->series.getName() << "(" << k << ") = ";
        setPrecision(precision);
        os <<res;
        if (!isnan(this->series.getAnalyticPrediction())){
            os << std::scientific << " (Delta = " << res - this->series.getAnalyticPrediction() << ")";
        }
        os << std::endl;
    }
}