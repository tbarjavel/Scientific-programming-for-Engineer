#ifndef DUMPER_SERIES_HH
#define DUMPER_SERIES_HH
#include "series.hh"

// This class represents the interface of the classes inheriting from DumperSeries.
class DumperSeries{
    public:
    DumperSeries(Series & s) : series(s){};        // Constructor
    virtual ~DumperSeries() {};                    // Destructor
    
    // Methods
    virtual void dump(std::ostream & os) = 0;      // Set dump
    virtual void setPrecision(unsigned int precision);     // Set Precision

    // Variables
    protected:
    Series & series;        // Set series object
};

inline std::ostream & operator <<(std::ostream & stream, DumperSeries & _this) {
    _this.dump(stream);
    return stream;
}


#endif