#ifndef SERIES_HH
#define SERIES_HH

// This class represents the interface of the family of classes inheriting from Series.
class Series {
	public:
	Series();                                   // Constructor
	virtual ~Series() {};                       // Destructor

	// Virtual methods
	virtual std::string getName() = 0;
	virtual double getAnalyticPrediction();
	virtual double getSumFromSeries(double s) = 0;
	virtual double getSumIncrement(unsigned int k) = 0;
	virtual double getSeriesFromSum(double s) = 0;

	// Defined methods
	double compute(unsigned int N);

	// Attributes
	unsigned int current_index;
	double current_value;
	unsigned int number_of_operations;	// Count how many operations have been computed
};

#endif