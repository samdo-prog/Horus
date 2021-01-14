#ifndef POLYNOM_H
#define POLYNOM_H

#include<ostream>
#include<iostream>
#include "DynamicArray.h"
#include <cmath>
#include "Complex.h"

class Polynom{
private:
	DynamicArray m_coef; // DynamicArray with all the coefficients of the polynom
	unsigned int m_degree; // Degree of the polynom

public:
	Polynom(); // Default constructor
	Polynom(const Polynom&); // copy constructor
	Polynom(const double* coef_array, int array_size); // Valued constructor (with an array of coefficient)
	~Polynom(); // Destructor

	virtual void set_coef(unsigned int index, double new_coef); // Set coefficient of a polynom
	virtual double get_coef(unsigned int index) const; // Get coefficient of a polynom
	virtual unsigned int get_degree() const; // Get degree of a polynom
	virtual std::ostream& printOn(std::ostream&) const; // Print a polynom

	Polynom operator=(const Polynom&);
	double operator()(double x); // Evaluate a polynom on a real point
	Complex operator[](Complex z); // Evaluate a polynom on a complex point

	//Operators between two polynoms
	friend Polynom operator+(const Polynom& a, const Polynom& b);
	friend Polynom operator-(const Polynom& a, const Polynom& b);
	friend Polynom operator*(const Polynom& a, const Polynom& b);
};

int testPolynom();

#endif
