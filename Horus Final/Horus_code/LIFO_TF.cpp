#include "LIFO_TF.h"

LIFO_TF::LIFO_TF() : m_LIFO_size(0), m_LIFO(new TransferFunction[0])
{
}

LIFO_TF::~LIFO_TF()
{
	delete[] m_LIFO;
}

unsigned int LIFO_TF::size() const
{
	return m_LIFO_size;
}

TransferFunction LIFO_TF::top() const
{
	if (m_LIFO_size > 0)
		return m_LIFO[m_LIFO_size-1];
	else
		throw(std::length_error("ERROR : LIFO is empty"));
}

void LIFO_TF::pop()
{
	if (m_LIFO_size > 0) {
		TransferFunction* buf = new TransferFunction[m_LIFO_size - 1];
		for (unsigned int i = 0; i < m_LIFO_size - 1; i++)
			buf[i] = m_LIFO[i];
		delete[] m_LIFO;
		m_LIFO = buf;
		m_LIFO_size = m_LIFO_size - 1;
	}
}

void LIFO_TF::push(TransferFunction& tf)
{
	if (m_LIFO_size < m_MAX_SIZE) {
		TransferFunction* buf = new TransferFunction[m_LIFO_size + 1];
		for (unsigned int i = 0; i < m_LIFO_size; i++)
			buf[i] = m_LIFO[i];
		buf[m_LIFO_size] = tf;
		delete[] m_LIFO;
		m_LIFO = buf;
		m_LIFO_size = m_LIFO_size + 1;
	}
	else {
		TransferFunction* buf = new TransferFunction[m_LIFO_size];
		for (unsigned int i = 1; i < m_LIFO_size; i++)
			buf[i-1] = m_LIFO[i];
		buf[m_LIFO_size-1] = tf;
		delete[] m_LIFO;
		m_LIFO = buf;
		m_LIFO_size = m_LIFO_size;
	}
}

std::ostream& LIFO_TF::printOn(std::ostream& os)
{
	for (unsigned int i = 0; i < m_LIFO_size; i++)
		m_LIFO[i].printOn(os);
	return os;
}

bool LIFO_TF::isEmpty() const
{
	return (m_LIFO_size == 0);
}

int test_LIFO_TF()
{
	TransferFunction H1;
	Polynom P;
	P.set_coef(0, 2);
	TransferFunction H2;
	H2.set_numerator(P);

	LIFO_TF lifo;
	for(int i = 0; i<9; i++)
		lifo.push(H1);
	lifo.push(H2);
	lifo.printOn(std::cout);
	return(0);
}
