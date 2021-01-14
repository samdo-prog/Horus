#ifndef SINUS_H
#define SINUS_H

#include "Signal.h"
#include <math.h>

class Sinus : public Signal {
private:
	double m_phase; // Phase of the signal
	double m_amplitude; // Amplitude of the signal
	double m_frequency; // Frequency of the signal
public :
	Sinus(int duration = 10, double amplitude = 1, double frequency = 1, double Ts = 1, double phase = 0, 
		int delay = 0); // Valued constructor
	double get_phase() const; // m_phase accessor
	double get_amplitude() const; // m_amplitude accessor
	void set_phase(double new_phase); // m_phase mutator
	void set_amplitude(double new_amplitude); // m_apmlitude mutator
};

int testSinus(); // Test function

#endif
