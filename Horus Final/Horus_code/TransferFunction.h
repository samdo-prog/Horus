#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include"Polynom.h"
#include"Ss.h"
#include"Signal.h"
#include "Step.h"
#include "Sinus.h"
#include "Ramp.h"

class TransferFunction {
private :
	Polynom m_numerator; // TF Numerator
	Polynom m_denominator; // TF Denominator
	double m_Te; // TF Sample time

protected:
	

public :
	
	TransferFunction(); // Default constructor
	TransferFunction(const TransferFunction&); // Copy constructor
	virtual ~TransferFunction(); //Destructor (calls polynom destructor)
	
	virtual void set_Te(double new_Te); // Sample time setting
	virtual double get_Te() const;
	virtual Polynom get_denominator() const; // Get denominator
	virtual Polynom get_numerator() const; // Get Numerator
	virtual void set_denominator(Polynom new_denominator) ; // Set denominator with a polynom
	virtual void set_numerator(Polynom new_numerator) ; // Set numerator with a polynom
	virtual double get_argument(double w);
	virtual double get_module(double w);
	virtual Matrix bode_module(double w_min, double w_max, unsigned int n_point);
	virtual Matrix bode_argument(double w_min, double w_max, unsigned int n_point);
	virtual Signal simulation(const Signal& input, Matrix& initial_conditions) const;
	virtual void log_numerator(const char* path);
	virtual void log_denominator(const char* path);
	virtual void log_Ts(const char* path);
	virtual void recover_numerator(const char* path);
	virtual void recover_denominator(const char* path);
	virtual void recover_Ts(const char* path);
	Matrix JArray() const;


	virtual Ss tf2ss() const; // From a TF to an SS
	
	virtual std::ostream& printOn(std::ostream&); // Print TF on an ostream
	
	TransferFunction operator=(const TransferFunction&);
	
	friend TransferFunction operator*(const TransferFunction& a, const TransferFunction& b);
	friend TransferFunction operator+(const TransferFunction& a, const TransferFunction& b);
	friend TransferFunction operator-(const TransferFunction& a, const TransferFunction& b);
	friend TransferFunction operator/(const TransferFunction& a, const TransferFunction& b);
};

int testTransfer(); // test function

#endif
