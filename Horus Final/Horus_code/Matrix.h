#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

class Matrix {
public:
	Matrix(); // Default constructor
	Matrix(int size); // Valued constructor (square matrix)
	Matrix(int raw, int column); // Valued constructor (n_line, n_column)
	Matrix(const Matrix&); // Copy constructor

	~Matrix(); // Destructor

	virtual void set_coef(unsigned int row, unsigned int column, double new_coef); // Set a matrix coefficient
	virtual double get_coef(int row, int column) const; // Get a coefficient in a matrix
	virtual int* get_size() const; // Get the size of the matrix
	void log(const char* path);
	
	virtual std::ostream& printOn(std::ostream&) const; // print a matrix
	virtual std::ostream& printJOn(std::ostream&) const; // print a jury matrix as a jury array
	double operator()(unsigned int row, unsigned int column); // operator to get a coefficient
	void operator()(unsigned int row, unsigned int column, double new_coef); // operator to set a coefficient
	Matrix operator=(const Matrix& a);

	friend Matrix operator+(const Matrix& a, const Matrix& b);
	friend Matrix operator-(const Matrix& a, const Matrix& b);
	friend Matrix operator*(const Matrix& a, const Matrix& b);
	friend Matrix operator~(const Matrix& a);

private:
	unsigned int m_l; // line number
	unsigned int m_c; // column number
	double** m_coef; // coefficient array
	static const unsigned int BLOCK_SIZE; // Default square matrix size

protected:
	virtual double** allocate(int raw, int column) const; // Dynamic allocation of an array
	virtual double** allocate(const Matrix&) const; // Dynamic allocation of an array similar to the array of the parameter
	virtual void assertIndex(unsigned int index_to_check, unsigned int limit_size) const; // Index error assertion
};

int testMatrix();

#endif