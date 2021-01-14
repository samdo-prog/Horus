#include "Ramp.h"

Ramp::Ramp(int duration, double slope, int delay, double Ts) : Signal(duration, delay, Ts), m_slope(slope)
{
	int k;
	for (int i = m_delay; i < m_values.get_size()[1]; i++) {
		k = i - m_delay;
		m_values(0, i, m_slope*k*m_Ts);
	}
}

double Ramp::get_slope() const
{
	return m_slope;
}

void Ramp::set_slope(double new_slope)
{
	m_slope = new_slope;
	for (int i = m_delay; i < m_values.get_size()[1]; i++) {
		int k = i - m_delay;
		m_values(0, i, new_slope * k * m_Ts);
	}
}

int testRamp()
{
	Ramp u0;
	Ramp u1(10);
	Ramp u2(12, 2.3);
	Ramp u3(9, 3.6, 2);

	u0.printOn(std::cout);
	u1.printOn(std::cout);
	u2.printOn(std::cout);
	u3.printOn(std::cout);

	Signal u4 = u0 + u0;

	(u4).printOn(std::cout);
	return(0);
}