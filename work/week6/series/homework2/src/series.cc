#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <ctgmath>
#include <cmath>

#include "series.hh"

Series::Series(){
    this->current_index = 0;
    this->current_value = 0;
    this->number_of_operations = 0;
}


double Series::compute(unsigned int N) {
    // Use inverse formula to get sum value from series value at current_index
    double sum = this->getSumFromSeries(this->current_value);

    // Increment sum from current_index to N
    for (double k = this->current_index + 1; k < N + 1; k++){
        sum += this->getSumIncrement(k);
    }

    // Use direct formula to get series value from sum value at final index
    this->current_value = this->getSeriesFromSum(sum);

    // Update number of operations and current index
    this->number_of_operations += N - this->current_index;
    this->current_index = N;

    // Return series value
    return this->current_value;
}


// Get Analytic Prediction of the implemented serie
double Series::getAnalyticPrediction(){
    return nan("");
}

