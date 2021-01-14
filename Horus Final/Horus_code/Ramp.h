#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Signal.h"

class Ramp : public Signal {
private:
	double m_slope; // Slope of the ramp

public:
	Ramp(int duration = 10, double slope = 1, int delay = 0, double Ts = 1); // Valued constructor
	
	double get_slope() const; // m_slope accessor
	void set_slope(double); // m_slope mutator
};

int testRamp(); // Test function

#endif
