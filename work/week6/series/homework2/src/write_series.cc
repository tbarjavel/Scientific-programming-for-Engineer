#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#include "write_series.hh"

// Constructor
WriteSeries::WriteSeries(Series& series, unsigned int maxiter, std::string separator) : DumperSeries(series) {
    this->maxiter = maxiter;
    this->separator = separator;
}

// Compute and write serie on file
void WriteSeries::dump(std::ostream & os) {
    // write sequential iterations to file
    std::string sname = this->series.getName();
    std::transform(sname.begin(), sname.end(), sname.begin(), ::tolower);
    std::string ext;
    if (this->separator == ",") {
        ext = ".csv";
    } else if (this->separator == "" || this->separator == "\\t") {
        // Re-assignment of space character to tab to preserve unique separator extension match
        this->separator = "\t";
        ext = ".txt";
    } else if (this->separator == "|") {
        ext = ".psv";
    }
    std::string filename = sname + ext;
    std::cout << "File " << filename.c_str() << " has been created." << std::endl;

    std::ofstream fout(filename.c_str());
    fout << "iteration" << this->separator << "value" << std::endl;
    for (unsigned int N = 1; N < this->maxiter + 1; ++N) {
        fout << N << separator << this->series.compute(N) << std::endl;
    }
    fout.close();
}
