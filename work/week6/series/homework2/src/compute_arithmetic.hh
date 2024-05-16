#ifndef COMPUTE_ARITHMETIC_HH
#define COMPUTE_ARITHMETIC_HH
#include "series.hh"

// This class inherits from Series and computes a simple summation serie
class ComputeArithmetic: public Series {
	public:
	ComputeArithmetic() : Series() {};		   // Constructor
	virtual ~ComputeArithmetic() {};           // Destructor

	// Methods
	std::string getName() override;			   // Get name of the implemented serie

	double getSumFromSeries(double s) override;
	double getSumIncrement(unsigned int k) override;
	double getSeriesFromSum(double s) override;

};

#endif