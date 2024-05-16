#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <vector>
#include <ctgmath>

#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "series.hh"
#include "print_series.hh"
#include "write_series.hh"
#include "dumper_series.hh"
#include <stdexcept>

/* -------------------------------------------------------------------------- */

int main(int argc, char ** argv) {

    // Check number of inputs
    try
    {
        // Throw error if number of inputs is < 3
        if (argc < 3)
        {
           throw std::invalid_argument("Error, not enough arguments. Please add series type ('ar' or 'pi') and number of iterations");
        }
        if (argc > 6)
        {
           throw std::invalid_argument("Error, too many arguments.");
        }
    }
    catch (std::invalid_argument &ex)
    {
        std::cout << ex.what() << '\n';
        return EXIT_SUCCESS;
    }

    // Parse arguments into stringstream
    std::stringstream sstr;
    for (int i = 1; i < argc; ++i) {
        // std::cout << argv[i] << std::endl;
        sstr << argv[i] << " ";
    }

    // Argument 1: series type ("ar" or "pi")
    std::string seriestype;
    sstr >> seriestype;

    // Argument 2: number of iterations
    unsigned int N;
    sstr >> N;

    // Argument 3: dump method ("print" or "write")
    std::string dumpmethod;
    sstr >> dumpmethod;

    // Argument 4 (conditional): frequency (for "print") or separator (for "write")
    unsigned int freq;
    std::string separator;
    if (dumpmethod == "print") {
        if (argc < 5){
            freq = 1;
        }else{
            sstr >> freq;
        }
    } else if (dumpmethod == "write") {
        if (argc < 5){
            separator = "\\t";
        }else{
            sstr >> separator;
        }
    }

    // Argument 5 (conditional): precision
    unsigned int precision;
    if (argc < 6){
        precision = 10;
    }else{
        sstr >> precision;
    }

    // Throw error if inputs are different from the expected ones
    try
    {
        // Throw error if series type is different from 'ai' or 'pi'
        if (seriestype.compare("ar") != 0 && seriestype.compare("pi") != 0) {
            throw std::invalid_argument("Error, series type can only be eithr 'ar' or 'pi' ");
        }

        // Throw error if number of iterations is <= 0
        if (N <= 0) {
            throw std::invalid_argument("Error, number of iterations must be higher than 0");
        }

        // Throw error if dump method is different from 'print' or 'write'
        if ((argc > 3) && (dumpmethod.compare("print") != 0 && dumpmethod.compare("write") != 0)) {
            throw std::invalid_argument("Error, dump method can only be eithr 'print' or 'write' ");
        }

        // Throw error if dump method is 'print' and freq is not a number
        if ((argc > 3) && (dumpmethod.compare("print") == 0 && freq == 0)) {
            throw std::invalid_argument("Error, if dump method is 'print' the frequency should be an integer");
        }

        // Throw error if dump method is 'write' and separator is not valid
        if ((argc > 3) && (dumpmethod.compare("write") == 0)) {

            // Search for a match with any of the valid separators
            std::vector<std::string> separators = {",", "|", "", "\\t"};
            int v = 0;
            std::for_each(
                separators.begin(),
                separators.end(),
                [separator, &v](auto &item) {v += separator.compare(item) == 0;}
            );

            // If no match, throw error
            if (v == 0) {
                std::cout << separator << std::endl;
                throw std::invalid_argument(
                    "Error, if dump method is 'write' the separator should be ',', '|', '', or '\\t' ");
            }
        }
    }
    catch (std::invalid_argument &ex)
    {
        std::cout << ex.what() << '\n';
        return EXIT_SUCCESS;
    }

    // Instanciate appropriate series object
    std::unique_ptr<Series> series; // doesn't point to anything yet
    if (seriestype == "ar") {
        series.reset(new ComputeArithmetic);
    } else if (seriestype == "pi") {
        series.reset(new ComputePi);
    }

    // Instanciate appropriate dumper object
    std::unique_ptr<DumperSeries> dumper; // doesn't point to anything yet
    if (dumpmethod == "print") {
        dumper.reset(new PrintSeries(*series, N, freq, precision));
    } else if (dumpmethod == "write") {
        dumper.reset(new WriteSeries(*series, N, separator));
    }

    // Print series result
    if (argc == 3) {
        std::cout << series->getName() << " result for " << N << " iterations is: " << series->compute(N) << std::endl;
    } else if (argc > 3){
        // dumper->dump(std::cout);
        std::cout << *dumper;
    }
    std::cout << "Number of operation performed = " << series->number_of_operations << std::endl;

    return EXIT_SUCCESS;
}

// 5.1) Initial complexity:
// Series from 1 to  N: S = sum(k=1 -> N, ...) -> O(N)
// Dumper series output from 1 to maxiter: sum(N=1 -> maxiter, sum(k=1 -> N, ...))
//                                         -> O(sum(N=1 -> maxiter, O(N))
//                                         -> O(maxiter*(maxiter + 1) / 2)
//
// 5.4) New complexity after series.cc modification:
// O(maxiter) !
//
// 5.5) With reversed computation of Pi, we cannot optimize the complexity of the dump method
// by storing intermediate values, hence complexity is bound to O(maxiter*(maxiter + 1) / 2)