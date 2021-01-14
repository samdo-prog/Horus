#ifndef LIFO_TF_H
#define LIFO_TF_H
#include "TransferFunction.h"
#include <iostream>

class LIFO_TF {
private:
	TransferFunction* m_LIFO; // Dynamic array composed of transfer functions
	unsigned int m_LIFO_size; // Size of the dynamic array
	const unsigned int m_MAX_SIZE = 10; // Max size of the stack
public:
	LIFO_TF(); // Default constructor
	~LIFO_TF();

	virtual unsigned int size() const; // m_LIFO_size accessor
	virtual TransferFunction top() const; // Top of the stack accessor
	virtual void pop(); // Delete the top of the stack
	virtual void push(TransferFunction& tf); // Push a TF on the top of the stack
	virtual std::ostream& printOn(std::ostream& os); // Print a stack
	virtual bool isEmpty() const; // Check whether or not the stack is empty
};

int test_LIFO_TF(); // Test function

#endif
