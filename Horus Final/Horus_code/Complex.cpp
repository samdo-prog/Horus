#include "Complex.h"
#include <cmath>
const double M_PI = 3.14159265358979323846;


Complex::Complex() : m_Re(1), m_Im(1)
{
}

Complex::Complex(double Re, double Im) : m_Re(Re), m_Im(Im)
{
}

Complex::Complex(const Complex& z)
{
	m_Re = z.get_Re();
	m_Im = z.get_Im();
}

Complex::~Complex()
{
}

double Complex::get_Re() const
{
	return m_Re;
}

double Complex::get_Im() const
{
	return m_Im;
}

void Complex::set_Re(double new_Re)
{
	m_Re = new_Re;
}

void Complex::set_Im(double new_Im)
{
	m_Im = new_Im;
}

double Complex::get_module() const
{
	double module = sqrt(pow(get_Re(),2)+pow(get_Im(), 2));
	return(module);
}

double Complex::get_argument() const
{
	double arg;
	arg = atan2(get_Im(), get_Re());
	if (get_Im() > 0)
		arg = arg - 2 * M_PI;

	return arg;
}

void Complex::polar(double mod, double arg)
{
	if (mod >= 0) {
		set_Re(mod * cos(arg));
		set_Im(mod * sin(arg));
	}
	else
		throw(std::invalid_argument("ERROR : The module must be positive"));
}

std::ostream& Complex::printOn(std::ostream& os)
{
	os << get_Re() << " + "  << get_Im() << " j" << std::endl;
	return(os);
}

Complex Complex::operator=(const Complex& z)
{
	if (&z != this) {
		m_Re = z.get_Re();
		m_Im = z.get_Im();
		return *this;
	}
}

Complex operator*(const Complex& z1, const Complex& z2)
{
	Complex z;
	z.set_Re(z1.get_Re()*z2.get_Re() - z1.get_Im()*z2.get_Im());
	z.set_Im(z1.get_Re()*z2.get_Im() + z2.get_Re()*z1.get_Im());
	return z;
}

Complex operator+(const Complex& z1, const Complex& z2)
{
	Complex z;
	z.set_Re(z1.get_Re() + z2.get_Re());
	z.set_Im(z1.get_Im() + z2.get_Im());
	return z;
}

Complex operator-(const Complex& z1, const Complex& z2)
{
	Complex z;
	z.set_Re(z1.get_Re() - z2.get_Re());
	z.set_Im(z1.get_Im() - z2.get_Im());
	return z;
}

Complex operator/(const Complex& z1, const Complex& z2)
{
	if (!(z1.get_Re() == 0 && z2.get_Im() == 0)) {
		Complex z;
		z.set_Re((z1 * ~z2).get_Re());
		z.set_Im((z1 * ~z2).get_Im());
		z = z / (z2 * ~z2).get_Re();
		return z;
	}
	else
		throw(std::invalid_argument("ERROR : Division by 0"));
}

Complex operator~(const Complex& z)
{
	Complex z_conj(z.get_Re(), -z.get_Im());
	return z_conj;
}

Complex operator*(const double a, const Complex& z)
{
	Complex z1(a*z.get_Re(), a*z.get_Im());
	return z1;
}

Complex operator/(const Complex& z, const double a)
{
	if (a != 0) {
		Complex z1(z.get_Re() / a, z.get_Im() / a);
		return z1;
	}
	else
		throw(std::invalid_argument("ERROR : Division by 0"));
}

Complex complex_pow(Complex& z, int n)
{
	Complex z1(1,0);
	for (int i = 0; i < n; i++) {
		z1 = z1 * z;
	}
	return z1;
}

int testComplex()
{
	Complex z1; //default constructor
	std::cout << "Default :" << std::endl;
	z1.printOn(std::cout);
	
	Complex z2(1, 1); //valued constructor
	std::cout << "Valued :" << std::endl;
	z2.printOn(std::cout);

	Complex z3(z1); // Copy constructor
	std::cout << "Copy (Default) :" << std::endl;
	z3.printOn(std::cout);

	std::cout << "Module (Default) : " << z1.get_module() << std::endl;
	std::cout << "Argument (Default) : " << z1.get_argument() << std::endl;

	z3.polar(1, 1); //Polar setting
	std::cout << "Polar (Module : 1 , Argument : 1) :" << std::endl;
	z3.printOn(std::cout);

	std::cout << "Operators between two complexes  (z1 (Default) , z3(Polar)) :" << std::endl; // Operators
	std::cout << "+ :" << std::endl;
	z2 = z1 + z3;
	z2.printOn(std::cout);
	std::cout << "- :" << std::endl;
	z2 = z1 - z3;
	z2.printOn(std::cout);
	std::cout << "* :" << std::endl;
	z2 = z1 * z3;
	z2.printOn(std::cout);
	std::cout << "/ :" << std::endl;
	z2 = z1 / z3;
	z2.printOn(std::cout);

	std::cout << "Conjugate (Default) :" << std::endl;
	(~z1).printOn(std::cout);

	std::cout << "Puissance n = 2 (Default) : " << std::endl;
	(complex_pow(z1, 2)).printOn(std::cout);

	return(0);
}
