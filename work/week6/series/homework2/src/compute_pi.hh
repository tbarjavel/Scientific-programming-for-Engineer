#ifndef COMPUTE_PI_HH
#define COMPUTE_PI_HH
#include "series.hh"

// This class inherits from Series and computes a serie converging to pi
class ComputePi : public Series {
	public:
	ComputePi() : Series() {};                   // Constructor
	virtual ~ComputePi() {};                     // Destructor

	// Methods
	std::string getName() override;				// Get name of the implemented serie
	double getAnalyticPrediction() override;	// Get analytic prediction of PI

	double getSumFromSeries(double s) override;
	double getSumIncrement(unsigned int k) override;
	double getSeriesFromSum(double s) override;
};

#endif

