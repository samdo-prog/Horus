#include "Matrix.h"

const unsigned int Matrix::BLOCK_SIZE = 2;

Matrix::Matrix() : m_c(BLOCK_SIZE),m_l(BLOCK_SIZE), m_coef(allocate(BLOCK_SIZE, BLOCK_SIZE))
{
}

Matrix::Matrix(int n) : m_coef(allocate(n,n)), m_c(n), m_l(n)
{
}

Matrix::Matrix(int l, int c) : m_coef(allocate(l, c)), m_l(l), m_c(c)
{
}

Matrix::Matrix(const Matrix& a) : m_coef(allocate(a)), m_c(a.m_c), m_l(a.m_l)
{
}

Matrix::~Matrix()
{
	for (unsigned int i = 0; i < m_l; i++)
		delete[] m_coef[i];
	delete[] m_coef;
}

void Matrix::set_coef(unsigned int i, unsigned int j, double new_coef)
{
	assertIndex(i, m_l);
	assertIndex(j, m_c);
	m_coef[i][j] = new_coef;
}

double Matrix::get_coef(int i, int j) const
{
	assertIndex(i, m_l);
	assertIndex(j, m_c);
	return m_coef[i][j];
}

int* Matrix::get_size() const
{
	int* size = new int[2];
	size[0] = m_l;
	size[1] = m_c;
	return size;
}

void Matrix::log(const char* path)
{
	std::ofstream of(path);
	for (int i = 0; i < get_size()[0]; i++) {
		for (int j = 0; j < get_size()[1]-1; j++) {
			of << get_coef(i, j) << "," ;
		}
		of << get_coef(i, get_size()[1] - 1);
		of << std::endl;
	}
}

std::ostream& Matrix::printOn(std::ostream& os) const
{
	for (unsigned int i = 0; i < m_l; i++) {
		for (unsigned int j = 0; j < m_c; j++) {
			os<< m_coef[i][j] << "  ";
		}
		os << std::endl;
	}
	os << std::endl;
	return os;
}

std::ostream& Matrix::printJOn(std::ostream& os) const
{
	for (int i = 0; i < get_size()[0]; i++) {
		for (int j = 0; j < get_size()[1] - i; j++)
			std::cout << get_coef(i, j) << " ";
		std::cout << std::endl;
		for (int j = get_size()[1] - 1 - i; j >= 0; j--)
			std::cout << get_coef(i, j) << " ";
		std::cout << std::endl;
	}
	return(os);
}

double Matrix::operator()(unsigned int i, unsigned int j)
{
	return get_coef(i,j);
}

void Matrix::operator()(unsigned int i, unsigned int j, double new_coef)
{
	set_coef(i, j, new_coef);
}

Matrix Matrix::operator=(const Matrix& a)
{
	if (&a != this) {
		m_coef = allocate(a);
		m_l = a.m_l;
		m_c = a.m_c;
		return *this;
	}
}


double** Matrix::allocate(int l, int c) const
{
	double** arr2D = new double* [l];
	for (int i = 0; i < l; i++) {
		arr2D[i] = new double[c];
	}
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < c; j++) {
			arr2D[i][j] = 0;
		}
	}
	return arr2D;
}

double** Matrix::allocate(const Matrix& a) const
{
	double** arr2D = new double* [a.m_l];
	for (unsigned int i = 0; i < a.m_l; i++) {
		arr2D[i] = new double[a.m_c];
	}
	for (unsigned int i = 0; i < a.m_l; i++) {
		for (unsigned int j = 0; j < a.m_c; j++) {
			arr2D[i][j] = a.m_coef[i][j];
		}
	}
	return arr2D;
}

void Matrix::assertIndex(unsigned int index, unsigned int size) const
{
	if (!(index < size)) {
		throw std::out_of_range("ERROR : Bad index");
	}
}


Matrix operator+(const Matrix& a, const Matrix& b)
{
	Matrix S(a);

	if (!(*a.get_size() == *b.get_size())) {
		throw std::length_error("ERROR : Incompatible sizes for addition (Matrix must have the same size)");
	}

	for (int i = 0; i < a.get_size()[0]; i++)
		for (int j = 0; j < a.get_size()[1]; j++)
			S.set_coef(i,j,a.get_coef(i,j)+b.get_coef(i,j));

	return S;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	Matrix S(a);

	if (!(*a.get_size() == *b.get_size())) {
		throw std::length_error("ERROR : Incompatible sizes for soustraction (Matrix must have the same size)");
	}

	for (int i = 0; i < a.get_size()[0]; i++)
		for (int j = 0; j < a.get_size()[1]; j++)
			S.set_coef(i, j, a.get_coef(i, j) - b.get_coef(i, j));

	return S;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
	if (!(a.get_size()[1] == b.get_size()[0]) && !((a.get_size()[0] == 1 && a.get_size()[1]) || (b.get_size()[0] == 1 && b.get_size()[1]))) {
		throw std::length_error("ERROR : Incompatible sizes for multiplication");
	}

	
	double buf(0);

	if (a.get_size()[0] == 1 && a.get_size()[1] == 1) {
		Matrix M(b.get_size()[0], b.get_size()[1]);
		for (int i = 0; i < b.get_size()[0]; i++) {
			for (int j = 0; j < b.get_size()[1]; j++) {
				M(i, j, a.get_coef(0, 0) * b.get_coef(i, j));
			}
		}
		return(M);
	}

	else if (b.get_size()[0] == 1 && b.get_size()[1] == 1) {
		Matrix M(a.get_size()[0], a.get_size()[1]);
		for (int i = 0; i < a.get_size()[0]; i++) {
			for (int j = 0; j < a.get_size()[1]; j++) {
				M(i, j, b.get_coef(0, 0) * a.get_coef(i, j));
			}
		}
		return(M);
	}

	else{
		Matrix M(a.get_size()[0], b.get_size()[1]);
		for (int i = 0; i < a.get_size()[0]; i++) {
			for (int j = 0; j < b.get_size()[1]; j++) {
				for (int k = 0; k < a.get_size()[1]; k++) {
					buf = buf + a.get_coef(i, k) * b.get_coef(k, j);
				}
				M.set_coef(i, j, buf);
				buf = 0;
			}
		}
		return M;
	}


	
}

Matrix operator~(const Matrix& a)
{
	Matrix T(a.get_size()[1], a.get_size()[0]);
	for (int i = 0; i < a.get_size()[1]; i++) {
		for (int j = 0; j < a.get_size()[1]; j++) {
			T.set_coef(i, j, a.get_coef(j, i));
		}
	}
	return T;
}

int testMatrix()
{
	std::cout << "Default :" << std::endl;
	Matrix A;
	A.printOn(std::cout);

	std::cout << "Valued (square) :" << std::endl;
	Matrix B(2);
	B.printOn(std::cout);

	std::cout << "Valued (i,j)  :" << std::endl;
	Matrix C(3, 1);
	C.printOn(std::cout);

	std::cout << "C size  :" << std::endl;
	std::cout << C.get_size()[0] << " X " << C.get_size()[1] << std::endl;

	C.set_coef(0, 0, 0.5);
	std::cout << "C modified  :" << std::endl;
	C.printOn(std::cout);

	std::cout << "C coef (0,0)  :" << std::endl;
	std::cout << C.get_coef(0, 0) << std::endl;

	Matrix D(C);
	std::cout << "Copy of C:" << std::endl;
	D.printOn(std::cout);

	std::cout << "Sum C + C:" << std::endl;
	Matrix S = C + C;
	S.printOn(std::cout);

	for (int i = 0; i < A.get_size()[0]; i++) {
		for (int j = 0; j < A.get_size()[1]; j++) {
			A(i, j, 2);
		}
	}

	A(1, 0, 0.8);

	std::cout << "A :" << std::endl;
	A.printOn(std::cout);

	std::cout << "A*A:" << std::endl;
	Matrix M = A * A;
	M.printOn(std::cout);

	std::cout << "M :" << std::endl;
	(M).printOn(std::cout);

	std::cout << "Example of vectorial multiplication (Ct*C):" << std::endl;
	Matrix V = ~C * C;
	V.printOn(std::cout);

	std::cout << "M(1,2):" << std::endl;
	std::cout << M(1, 0) << std::endl;

	Matrix G = A;
	G.printOn(std::cout);

	return(0);
}