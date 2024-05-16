#ifndef WRITE_HH
#define WRITE_HH
#include "dumper_series.hh"

// This class writes the implemented serie steps on a file
class WriteSeries: public DumperSeries {
    public:
    WriteSeries(Series & series, unsigned int maxiter, std::string separator); // Constructor
    virtual ~WriteSeries() {};      // Destructor

    // Methods
    void dump(std::ostream & os) override;
    
    // Variables
    private:
    unsigned int maxiter;
    std::string separator;
};

#endif