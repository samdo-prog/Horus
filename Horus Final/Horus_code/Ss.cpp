#include "Ss.h"

Ss::Ss() : m_Te(1), m_A(2), m_B(2,1), m_C(1,2), m_D(1,1)
{
}

Ss::Ss(Matrix A, Matrix B, Matrix C, Matrix D, double Te) : m_Te(Te), m_A(A), m_B(B), m_C(C), m_D(D)
{
	assertSSDim(A, B, C, D);
}

Matrix Ss::get_A() const
{
	return m_A;
}

Matrix Ss::get_B() const
{
	return m_B;
}

Matrix Ss::get_C() const
{
	return m_C;
}

Matrix Ss::get_D() const
{
	return m_D;
}

double Ss::get_Te() const
{
	return m_Te;
}

void Ss::set_Te(double Te)
{
	m_Te = Te;
}

std::ostream& Ss::printOn(std::ostream& os) const
{
	os << "x(k+1) = Ax(k) + Bu(k)" << std::endl;
	os << "y(k) = Cx(k) + Du(k)" << std::endl <<std::endl;
	os << "A" << std::endl;
	m_A.printOn(os);
	os << "B" << std::endl;
	m_B.printOn(os);
	os << "C" << std::endl;
	m_C.printOn(os);
	os << "D" << std::endl;
	m_D.printOn(os);
	return os;
}

void Ss::assertSSDim(Matrix A, Matrix B, Matrix C, Matrix D)
{
	const unsigned int n = A.get_size()[0];
	const unsigned int p = 1;
	const unsigned int m = 1;
	if (!(A.get_size()[1] == n && B.get_size()[0] == n && C.get_size()[1] == n)) {
		throw(std::length_error("ERROR : Bad matrix dimensions in the state space representation (system must be a SISO)"));
	}
	if (!(D.get_size()[0] == m && C.get_size()[0] == m)) {
		throw(std::length_error("ERROR : Bad matrix dimensions in the state space representation (system must be a SISO)"));
	}
	if (!(D.get_size()[1] == p && B.get_size()[1] == p)) {
		throw(std::length_error("ERROR : Bad matrix dimensions in the state space representation (system must be a SISO)"));
	}
}

int testSs()
{
	Ss ss1;
	
	Matrix A(2, 2);
	Matrix B(2, 1);
	Matrix C(1, 2);
	Matrix D(1, 1);
	Ss ss2(A,B,C,D,1);

	ss1.printOn(std::cout);
	ss2.printOn(std::cout);
	return 0;
}
