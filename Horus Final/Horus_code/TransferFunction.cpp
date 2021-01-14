#include "TransferFunction.h"

TransferFunction::TransferFunction() : m_Te(1)
{
	Polynom d;
	d.set_coef(0, 1);
	d.set_coef(1, 1);
	Polynom n;
	n.set_coef(0, 1);
	m_denominator = d;
	m_numerator = n;
}

TransferFunction::TransferFunction(const TransferFunction& h) : m_Te(h.m_Te), m_numerator(h.m_numerator), m_denominator(h.m_denominator)
{
}

TransferFunction::~TransferFunction()
{
}

void TransferFunction::set_Te(double Te)
{
	if (Te > 0)
		m_Te = Te;
	else
		throw(std::invalid_argument("ERROR : Ts must be greater than 0"));
}

double TransferFunction::get_Te() const
{
	return m_Te;
}

Polynom TransferFunction::get_denominator() const
{
	return m_denominator;
}

Polynom TransferFunction::get_numerator() const
{
	return m_numerator;
}

void TransferFunction::set_numerator(Polynom numerator)
{
	m_numerator = numerator;
}

double TransferFunction::get_argument(double w)
{
	Complex z;
	z.polar(1, w * get_Te());
	double arg = (get_numerator()[z] / get_denominator()[z]).get_argument();
	return arg;
}

double TransferFunction::get_module(double w)
{
	Complex z;
	z.polar(1, w * get_Te());
	double mod = 20*log10( (get_numerator()[z] / get_denominator()[z]).get_module() );
	return mod;
}

Matrix TransferFunction::bode_module(double w_min, double w_max, unsigned int n_point)
{
	if ((w_min < w_max) && (w_max > 0) && (w_min > 0)) {
		Matrix module(n_point, 2);
		for (unsigned int i = 0; i < n_point; i++) {
			module(i, 1, get_module(i * (w_max - w_min) / n_point + w_min));
			module(i, 0, i * (w_max - w_min) / n_point + w_min);
		}
		return module;
	}
	else
		throw(std::invalid_argument("ERROR : Incompatible parameters for the bode diagram"));
}

Matrix TransferFunction::bode_argument(double w_min, double w_max, unsigned int n_point)
{
	if ((w_min < w_max) && (w_max > 0) && (w_min > 0)) {
		Matrix argument(n_point, 2);
		for (unsigned int i = 0; i < n_point; i++) {
			argument(i, 1, get_argument(i * (w_max - w_min) / n_point + w_min));
			argument(i, 0, i * (w_max - w_min) / n_point + w_min);
		}
		return argument;
	}
	else
		throw(std::invalid_argument("ERROR : Incompatible parameters for the bode diagram"));
}

Signal TransferFunction::simulation(const Signal& input, Matrix& x0) const
{
	int n = get_denominator().get_degree();
	Signal output(input.get_duration(), input.get_delay(), input.get_Ts());
	Matrix y(1, output.get_duration() + 1);
	Matrix x(n, 1);
	Matrix u(1,1);

	Ss ss = tf2ss();
	Matrix A = ss.get_A();
	Matrix B = ss.get_B();
	Matrix C = ss.get_C();
	Matrix D = ss.get_D();

	for (int k = 0; k < n; k++)
		x(k, 0, x0(k,0));

	for (int k = 0; k < output.get_duration() + 1; k++) {
		y.set_coef(0,k,(C*x)(0,0));
		u(0, 0, input.get_signal()(0, k));
		x = A * x + B * u;
	}
	
	output.set_signal(y);

	return output;
}

void TransferFunction::log_numerator(const char* path)
{
	unsigned p = get_numerator().get_degree();

	std::ofstream of(path);

	for (unsigned int i = 0; i < p; i++)
		of << get_numerator().get_coef(i) << " ";
	of << get_numerator().get_coef(p);
}

void TransferFunction::log_denominator(const char* path)
{
	unsigned n = get_denominator().get_degree();

	std::ofstream of(path);

	for (unsigned int i = 0; i < n; i++)
		of << get_denominator().get_coef(i) << " ";
	of << get_denominator().get_coef(n);
}

void TransferFunction::log_Ts(const char* path)
{
	std::ofstream of(path);
	of << get_Te();
}


void TransferFunction::recover_numerator(const char* path)
{
	std::ifstream of(path);
	if (of) {
		unsigned int index = 0;
		double buf;
		while (of >> buf) {
			m_numerator.set_coef(index, buf);
			index++;
		}
		of.close();
	}

	else
		std::cout << std::endl << "! No autosave file for the numerator !" << std::endl;
}

void TransferFunction::recover_denominator(const char* path)
{
	std::ifstream of(path);
	if (of) {
		unsigned int index = 0;
		double buf;
		while (of >> buf) {
			m_denominator.set_coef(index, buf);
			index++;
		}
		of.close();
	}

	else
		std::cout << std::endl << "! No autosave file for the denominator !" << std::endl;
}

void TransferFunction::recover_Ts(const char* path)
{
	double Ts;
	std::fstream of(path);
	if (of) {
		of >> Ts;
		set_Te(Ts);
		of.close();
	}
	else
		std::cout << std::endl << "! No autosave file for the Ts !" << std::endl;
}

Matrix TransferFunction::JArray() const
{
	bool stab_flag = true;
	Polynom D = get_denominator();
	int n = D.get_degree();

	if (!(D(1) > 0))
		stab_flag = false;
	if (!(std::pow(-1, n) * D(-1) > 0))
		stab_flag = false;

	if (n > 2) {
		Matrix jarray(n - 1, n + 1); // taille du tableau de Jury
		for (int i = 0; i < n + 1; i++) {
			jarray(0, i, D.get_coef(i));
		}

		if (!(std::abs(jarray(0, 0)) < jarray(0, n)))
			stab_flag = false;

		for (int i = 0; i < jarray.get_size()[0] - 1; i++) {
			for (int j = 0; j < n - i; j++) {
				jarray(i + 1, j, jarray(i, 0) * jarray(i, j) - jarray(i, n - i) * jarray(i, n - i - j));
			}
		}

		for (int i = 1; i < jarray.get_size()[0]; i++)
			if (!(std::abs(jarray(i, 0)) > std::abs(jarray(i, n - i))))
				stab_flag = false;

		if (stab_flag)
			std::cout << "=> The system is stable <=" << std::endl;
		else
			std::cout << "=> The system is unstable <=" << std::endl;

		return jarray;
	}

	else {
		Matrix jarray(1, n + 1); // taille du tableau de Jury
		for (int i = 0; i < n + 1; i++) {
			jarray(0, i, D.get_coef(i));
		}

		if (!(std::abs(D.get_coef(0)) < std::abs(D.get_coef(n))))
			stab_flag = false;

		if (stab_flag)
			std::cout << "=> The system is stable <=" << std::endl;
		else
			std::cout << "=> The system is unstable <=" << std::endl;

		return jarray;
	}
}

Ss TransferFunction::tf2ss() const
{
	Polynom N = get_numerator();
	Polynom D = get_denominator();
	int n = D.get_degree();
	int m = N.get_degree();

	if (n <= m) {
		throw(std::length_error("ERROR : To use tf2ss(), order must be greater than class"));
	}

	Matrix A(n);
	Matrix B(n, 1);
	Matrix C(1,n);
	Matrix E(1);

	for (int i = 0; i < n-1; i++) {
		A(i, i+1, 1);
	}
	for (int i = 0; i < n; i++) {
		A(n - 1, i, -D.get_coef(i));
	}

	B(n - 1, 0, 1);

	for (int i = 0; i < n; i++) {
		C(0, i, N.get_coef(i));
	}

	Ss ss(A, B, C, E, m_Te);

	return ss;
}

void TransferFunction::set_denominator(Polynom denominator)
{
	if (!(denominator.get_coef(0) == 0 && denominator.get_degree() == 0))
		m_denominator = denominator;
	else
		throw(std::invalid_argument("ERROR : Division by 0, try another denominator"));
}

std::ostream& TransferFunction::printOn(std::ostream& os)
{
	m_numerator.printOn(std::cout);
	std::cout << "--------------" << std::endl;
	m_denominator.printOn(std::cout);
	std::cout << "Ts = " << m_Te << std::endl;
	std::cout << std::endl;
	return(os);
}

TransferFunction TransferFunction::operator=(const TransferFunction& a)
{
	if (this != &a) {
		m_denominator = a.get_denominator();
		m_numerator = a.get_numerator();
		m_Te = a.get_Te();
		return *this;
	}
}

TransferFunction operator*(const TransferFunction& a, const TransferFunction& b)
{
	if (a.get_Te() == b.get_Te()) {
		TransferFunction c;
		c.set_denominator(b.get_denominator() * a.get_denominator());
		c.set_numerator(b.get_numerator() * a.get_numerator());
		c.set_Te(a.get_Te());
		return(c);
	}
	else
		throw (std::invalid_argument("ERROR : The operations with multiple TF require the same Ts"));
}

TransferFunction operator+(const TransferFunction& a, const TransferFunction& b)
{
	if (a.get_Te() == b.get_Te()) {
		TransferFunction c;
		c.set_denominator(a.get_denominator() * b.get_denominator());
		c.set_numerator(a.get_numerator() * b.get_denominator() + b.get_numerator() * a.get_denominator());
		c.set_Te(a.get_Te());
		return(c);
	}
	else
		throw (std::invalid_argument("ERROR : The operations with multiple TF require the same Ts"));
}

TransferFunction operator-(const TransferFunction& a, const TransferFunction& b)
{
	if (a.get_Te() == b.get_Te()) {
		TransferFunction c;
		c.set_denominator(a.get_denominator() * b.get_denominator());
		c.set_numerator(a.get_numerator() * b.get_denominator() - b.get_numerator() * a.get_denominator());
		c.set_Te(a.get_Te());
		return(c);
	}
	else
		throw (std::invalid_argument("ERROR : The operations with multiple TF require the same Ts"));

}

TransferFunction operator/(const TransferFunction& a, const TransferFunction& b)
{
	if (a.get_Te() == b.get_Te()) {
		TransferFunction c;
		c.set_denominator(a.get_denominator() * b.get_numerator());
		c.set_numerator(a.get_numerator() * b.get_denominator());
		c.set_Te(a.get_Te());
		return(c);
	}
	else
		throw (std::invalid_argument("ERROR : The operations with multiple TF require the same Ts"));
}

int testTransfer() {
	TransferFunction H1;
	TransferFunction H11(H1);
	H11.printOn(std::cout);

	TransferFunction H2;
	H1.printOn(std::cout);

	double coef_N2[] = { 0.04954, 0.04954 };
	Polynom N2(coef_N2, 2);
	double coef_D2[] = {1, -2.043, 1};
	Polynom D2(coef_D2, 3);
	H2.set_denominator(D2);
	H2.set_numerator(N2);
	H2.printOn(std::cout);

	TransferFunction P = H1 * H2 * H1; // test multiplication

	TransferFunction S = H1 + H1; // test addition

	TransferFunction M = H1 - H1; //test soustraction

	TransferFunction D = H1 / H2; //test division

	P.printOn(std::cout);
	S.printOn(std::cout);
	M.printOn(std::cout);
	D.printOn(std::cout);
	
	Ss ssP = H2.tf2ss();
	ssP.printOn(std::cout);

	int duration = 10;
	double amplitude = 1.0;
	double frequency = 10;
	double Ts = 0.0066;
	double phase = 0;
	int delay = 0;

	Step e(duration, amplitude, delay, Ts);
	

	Matrix ic(2,1);
	H2.simulation(e, ic).log("DATA/output.txt");

	e.printOn(std::cout);
	e.log("DATA/input.txt");

	Matrix H2Jury = H2.JArray();
	H2Jury.printOn(std::cout);

	Matrix mod = H2.bode_module(0.1, 3, 100);
	mod.log("DATA/bode_module.txt");

	Matrix arg = H2.bode_argument(0.1, 3, 100);
	arg.log("DATA/bode_argument.txt");
	return(0);
}
