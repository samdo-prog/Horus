#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class Complex{
private:
	double m_Re; // Real part
	double m_Im; // Imaginary part

public:
	Complex(); // Default constructor
	Complex(double Re, double Im); // Valued constrcuctor
	Complex(const Complex&); // Copy constructor

	~Complex(); // Destructor

	virtual double get_Re() const; // Real part accessor
	virtual double get_Im() const; // Imaginary part accessor

	virtual void set_Re(double new_Re); // Real part mutator
	virtual void set_Im(double new_Im); // Imaginary part mutator

	virtual double get_module() const; // Get the module of the number
	virtual double get_argument() const; // Get the argument of the number

	virtual void polar(double mod, double arg); // Set the number with polar arguments

	virtual std::ostream& printOn(std::ostream& os); // Print the number

	Complex operator=(const Complex& z);

	// Operator between complexes
	friend Complex operator*(const Complex& z1, const Complex& z2);
	friend Complex operator+(const Complex& z1, const Complex& z2);
	friend Complex operator-(const Complex& z1, const Complex& z2);
	friend Complex operator/(const Complex& z1, const Complex& z2);
	friend Complex operator~(const Complex& z); // Conjugate a number
	
	// Operator between scalar and complexes
	friend Complex operator*(const double a, const Complex& z);
	friend Complex operator/(const Complex& z, const double a);

	// Complex power
	friend Complex complex_pow(Complex& z, int i);
};

// Test function
int testComplex();

#endif

