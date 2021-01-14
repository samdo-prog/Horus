#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>

class DynamicArray {
public:
	DynamicArray(); // Default constructor
	DynamicArray(int size); // Valued constructor (with size of the array)
	DynamicArray(const DynamicArray&); // Copy constructor
	virtual ~DynamicArray(); // Destructor

	virtual void grow(); // Memory allocation filled with 0 (size of BLOCK_SIZE)
	virtual unsigned int blockSize() const; // get BLOCK_SIZE
	virtual unsigned int size() const; // get size of a dynamic array

	virtual std::ostream& printOn(std::ostream&) const; // print a dynamic array

	virtual double get(unsigned int index) const; // get a value of a dynamic array
	virtual void set(unsigned int index, double new_coef); // set a value in a dynamic array
	DynamicArray& operator=(const DynamicArray a);

protected:
	void assertIndex(unsigned int index) const; // Assertion for index problems
	virtual double* allocate(unsigned int size) const; // Allocate empty memory
	virtual double* allocate(const DynamicArray&) const; // Memory allocation filled with values of another dynamic array (size of BLOCK_SIZE)


private:
	double* data; // coefficients
	unsigned int data_size; // array size
	static const unsigned int BLOCK_SIZE; // Allocation size
};

#endif