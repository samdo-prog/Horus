#include "Signal.h"

Signal::Signal(int duration, int delay, double Ts) : m_duration(duration), m_values(1,duration+1), m_delay(delay), m_Ts(Ts)
{
	
}

void Signal::set_signal(Matrix& new_matrix)
{
	m_values = new_matrix;
	m_duration = new_matrix.get_size()[1] - 1;
}

Matrix Signal::get_signal() const
{
	return m_values;
}

int Signal::get_duration() const
{
	return m_duration;
}

int Signal::get_delay() const
{
	return m_delay;
}

double Signal::get_Ts() const
{
	return m_Ts;
}

void Signal::set_Ts(double new_Ts)
{
	m_Ts = new_Ts;
}

std::ostream& Signal::printOn(std::ostream& os)
{
	m_values.printOn(os);
	return(os);
}

void Signal::log(const char* path)
{
	std::ofstream of(path);
	if (of) {
		for (int i = 0; i < get_signal().get_size()[1]; i++)
			of << i * m_Ts << "," << get_signal()(0, i) << std::endl;
	}
	else {
		"Unable to find 'log.txt'";
	}
}

Signal Signal::operator=(const Signal& a)
{
	if (&a != this) {
		m_values = a.get_signal();
		m_duration = a.get_duration();
		m_delay = a.get_delay();
		m_Ts = a.get_Ts();
		return *this;
	}
}

Signal operator+(const Signal& a, const Signal& b)
{
	Matrix new_signal = a.get_signal()+b.get_signal();
	Signal s;
	s.set_signal(new_signal);
	return (s);
}
