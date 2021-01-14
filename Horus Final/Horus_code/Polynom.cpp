#include "Polynom.h"
#include "DynamicArray.h"

Polynom::Polynom(): m_coef(DynamicArray(3)), m_degree(0)
{
}

Polynom::Polynom(const Polynom& polynom): m_coef(polynom.m_coef), m_degree(polynom.m_degree) {

}

Polynom::Polynom(const double* tab_coef, int tab_size)
{
	for (int i = 0; i < tab_size; i++
		) {
		set_coef(i,tab_coef[i]);
	}
}

Polynom::~Polynom()
{
}

void Polynom::set_coef(unsigned int index, double coef)
{
	while (index >= m_coef.size() - 1)
		m_coef.grow();
	m_coef.set(index, coef);
	if (coef != 0)
		if (index > m_degree)
			m_degree = index;

}

double Polynom::get_coef(unsigned int index) const
{
	if (index > m_degree) {
		return 0;
	}
	else {
		return m_coef.get(index);
	}
}

unsigned int Polynom::get_degree() const
{
	return m_degree;
}

std::ostream& Polynom::printOn(std::ostream& os) const
{	
	for (unsigned int i = 0; i < m_degree; i++) {
		if (m_coef.get(i) != 0)
			os << m_coef.get(i) << "z^" << i << " + ";
	}
	os << m_coef.get(m_degree) << "z^" << m_degree << std::endl;
	return os;
}

Polynom Polynom::operator=(const Polynom& a)
{
	if (&a != this) {
		unsigned int n = a.get_degree();

		if (get_degree() > a.get_degree())
			n = get_degree();

		for (unsigned int i = 0; i < n + 1; i++)
			set_coef(i, a.get_coef(i));

		m_degree = a.get_degree();

		return(*this);
	}
}

double Polynom::operator()(double x)
{
	double y = 0;
	for (unsigned int i = 0; i <= get_degree(); i++)
		y = y + get_coef(i) * (std::pow(x,i));
	return y;
}

Complex Polynom::operator[](Complex z)
{
	Complex z1(0,0);
	for (unsigned int i = 0; i <= get_degree(); i++)
		z1 = z1 + get_coef(i) * (complex_pow(z, i));
	return z1;
}

Polynom operator+(const Polynom& a, const Polynom& b)
{
	Polynom c;
	unsigned int n = a.get_degree();
	if (b.get_degree() > a.get_degree())
		n = b.get_degree();

	for (unsigned int i = 0; i <= n + 1; i++)
		c.set_coef(i, a.get_coef(i) + b.get_coef(i));
	return(c);
}

Polynom operator-(const Polynom& a, const Polynom& b)
{
	Polynom c;
	unsigned int n = a.get_degree();
	if (b.get_degree() > a.get_degree())
		n = b.get_degree();

	for (unsigned int i = 0; i <= n; i++)
		c.set_coef(i, a.get_coef(i) - b.get_coef(i));

	return(c);
}

Polynom operator*(const Polynom& a, const Polynom& b) {
	Polynom c;
	for (unsigned int i=0; i < a.get_degree() + 1; i++) {
		for (unsigned int j = 0; j < b.get_degree() + 1; j++) {
			c.set_coef(i + j, c.get_coef(i+j)+a.get_coef(i) * b.get_coef(j));
		}
	}
	return(c);
}

int testPolynom() {
	Polynom P; //par default
	Polynom Q; // par recopie
	std::cout << "P (par defaut) : " << std::endl;
	P.printOn(std::cout);
	std::cout << "Degree : " << P.get_degree() << std::endl;
	std::cout << "Q (par recopie) : " << std::endl;
	Q.printOn(std::cout);
	Q.set_coef(5, 5.8);// modification du coeficient du 5 ieme degre et de degre 0
	Q.set_coef(0, 2.6);
	std::cout << "Q (modif coef) : " << std::endl;
	Q.printOn(std::cout);
	std::cout << "Degree : " << Q.get_degree() << std::endl;
	P.set_coef(1000, 9);
	P.set_coef(6, 2);
	P.set_coef(1, 3);
	P = Q; // test de l'operateur d'affectation
	std::cout << "P (egale a Q) : " << std::endl;
	P.printOn(std::cout);
	std::cout << "Degree : " << P.get_degree() << std::endl;
	P.set_coef(6, 2); //Modification de P au degré 6 et 3
	P.set_coef(3, 1);
	std::cout << "P (modif coef) : " << std::endl;
	P.printOn(std::cout);
	std::cout << "Degree : " << P.get_degree() << std::endl;
	Polynom A = P + Q; // addition polynomiale de p et q
	std::cout << "A = P + Q: " << std::endl;
	A.printOn(std::cout);
	std::cout << "Degree : " << A.get_degree() << std::endl;
	Polynom S = P - Q; // addition polynomiale de p et q
	std::cout << "S = P - Q: " << std::endl;
	S.printOn(std::cout);
	std::cout << "Degree : " << S.get_degree() << std::endl;
	Polynom M = P * Q; // multiplication polynomiale
	std::cout << "M = P x Q: " << std::endl;
	M.printOn(std::cout);
	std::cout << "Degree : " << M.get_degree() << std::endl;
	double coef_z[] = { 1,2,3,2,2,2,0 };
	Polynom Z = Polynom(coef_z, 6);
	Z.printOn(std::cout);
	std::cout << "Degree : " << Z.get_degree() << std::endl;
	std::cout << "Z(1) : " << Z(1) << std::endl;
	Complex z;
	Complex Y = Q[z];
	Y.printOn(std::cout);
	return(0);
}