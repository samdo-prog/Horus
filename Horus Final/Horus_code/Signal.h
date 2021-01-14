#include "Matrix.h"
#include <fstream>
#ifndef SIGNAL_H
#define SIGNAL_H

class Signal{
protected:
	int m_duration; // Number of samples in the signal
	Matrix m_values; // Matrix of the values
	int m_delay; // Delay before signal start
	double m_Ts; // Sample time

public:
	Signal(int duration = 10, int delay = 0, double Ts = 1); // valued constructor
	virtual Matrix get_signal() const; // m_values accessor
	virtual int get_duration() const; // m_duration accessor
	virtual int get_delay() const; // m_delay accessor
	virtual double get_Ts() const; // m_Ts accessor
	virtual void set_Ts(double new_Ts); // m_Ts mutator
	void set_signal(Matrix& new_matrix); // m_values mutator


	std::ostream& printOn(std::ostream&); // Print a signal
	void log(const char* path); // Log a signal on a file

	// Operators between signals 
	Signal operator=(const Signal& u);
	friend Signal operator+(const Signal& a, const Signal& b);
};

#endif SIGNAL_H
