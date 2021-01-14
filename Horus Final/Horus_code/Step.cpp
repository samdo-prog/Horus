#include "Step.h"

Step::Step(int duration, double amplitude, int delay, double Ts) : Signal(duration, delay, Ts), m_amplitude(amplitude)
{
	for (int i = m_delay; i < m_values.get_size()[1]; i++) {
			m_values(0, i, m_amplitude);
	}
}

void Step::set_amplitude(double new_amplitude)
{
	for (int i = m_delay; i < m_values.get_size()[1]; i++) {
		m_values(0, i, new_amplitude);
	}
}

double Step::get_amplitude() const
{
	return m_amplitude;
}

int testStep()
{
	Step u0;
	Step u1(12,2.3);
	Step u2(9, 3.6, 2);

	u0.printOn(std::cout);
	u1.printOn(std::cout);
	u2.printOn(std::cout);

	u0.log("DATA/input.txt");
	return(0);
}
