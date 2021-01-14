#ifndef SS_H
#define SS_H

#include "Matrix.h"
#include <iostream>

class Ss {
private:
	// Matrices of the state representation
	Matrix m_A;
	Matrix m_B;
	Matrix m_C;
	Matrix m_D;

	double m_Te; // Sample time

public:
	Ss();
	Ss(Matrix, Matrix, Matrix, Matrix, double);
	
	// Accessors to the matrices of the state representation
	virtual Matrix get_A() const;
	virtual Matrix get_B() const;
	virtual Matrix get_C() const;
	virtual Matrix get_D() const;

	virtual double get_Te() const; // m_Te accessor
	virtual void set_Te(double Te); // m_Te mutator
	
	virtual std::ostream& printOn(std::ostream&) const; // Print a state space representation are valid

protected:
	virtual void assertSSDim(Matrix, Matrix, Matrix, Matrix); // Check if the dimension of the matrices are 

};

int testSs(); // Test function

#endif