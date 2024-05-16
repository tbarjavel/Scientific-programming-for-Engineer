#ifndef PRINT_HH
#define PRINT_HH
#include "dumper_series.hh"

// This class displays the implemented serie steps
class PrintSeries : public DumperSeries {
    public:
    PrintSeries(Series & series, unsigned int maxiter, unsigned int frequency,unsigned int precision);   // Constructor
    virtual ~PrintSeries() {}; // Destructor

    // Methods
    void dump(std::ostream & os = std::cout) override;      // override dump method
    void setPrecision(unsigned int precision) override;     // override setPrecision method

    // Variables
    private:
    unsigned int maxiter;
    unsigned int frequency;
    unsigned int precision;
};

#endif