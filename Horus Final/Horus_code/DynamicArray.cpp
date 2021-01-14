#include "DynamicArray.h"
#include <sstream>

const unsigned int DynamicArray::BLOCK_SIZE = 2;

DynamicArray::DynamicArray() : data(allocate(BLOCK_SIZE)), data_size(BLOCK_SIZE) {

}

DynamicArray::~DynamicArray() {
	delete[]data;
}

DynamicArray::DynamicArray(int sz) : data(allocate(sz)), data_size(sz) {

}

DynamicArray::DynamicArray(const DynamicArray& a) :
	data(allocate(a)), data_size(a.data_size)
{
}

double* DynamicArray::allocate(unsigned int sz) const {
	double* buffer = new double[sz];
	for (unsigned int i = 0; i < sz; i++)
		buffer[i] = 0;
	return buffer;
}

double* DynamicArray::allocate(const DynamicArray& a) const {
	double* buffer = new double[a.data_size];
	for (unsigned int i = 0; i < a.data_size; i++)
		buffer[i] = a.data[i];
	return buffer;
}

void DynamicArray::grow() {
	const unsigned int sz = data_size + BLOCK_SIZE;
	double* buffer = allocate(sz);

	for (unsigned int i = 0; i < data_size; i++) {
		buffer[i] = data[i];
	}

	delete[] data;

	data = buffer;
	data_size = sz;

}

unsigned int DynamicArray::size() const {
	return data_size;
}

unsigned int DynamicArray::blockSize() const {
	return BLOCK_SIZE;
}

std::ostream& DynamicArray::printOn(std::ostream& os) const {
	os << '[';

	for (unsigned int i = 0; i < data_size; i++)
		os << data[i] << ' ';

	os << ']';
	return os;
}

double DynamicArray::get(unsigned int i) const {
	return data[i];
}

void DynamicArray::set(unsigned int i, double value)
{
	data[i] = value;
}

void DynamicArray::assertIndex(unsigned int index) const
{
	if (index > data_size - 1) {
		std::ostringstream os;
		os << index;
		throw std::out_of_range(os.str());
	}
}

DynamicArray& DynamicArray::operator=(const DynamicArray a) {
	if (&a != this)
		data = allocate(a);
	return *this;

}