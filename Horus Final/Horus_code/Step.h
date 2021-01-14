#ifndef STEP_H
#define STEP_H
#include "Signal.h"

class Step : public Signal {
private:
	double m_amplitude;
	
public:
	Step(int duration = 10, double amplitude=1, int delay=0, double Ts=1);
	void set_amplitude(double new_amplitude);
	double get_amplitude() const;
};

int testStep();

#endif
