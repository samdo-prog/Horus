#include "Sinus.h"

const double M_PI = 3.14159265358979323846;

Sinus::Sinus(int duration, double amplitude , double frequency, double Ts, double phase, int delay) : Signal(duration, delay, Ts), m_amplitude(amplitude), m_frequency(frequency), m_phase(phase)
{
	int k;
	double phi;
	for (int i = m_delay; i < m_values.get_size()[1]; i++) {
		k = i - m_delay;
		phi = m_phase * M_PI / 180;
		m_values(0, i, m_amplitude * sin(2 * M_PI * m_frequency * k * m_Ts + phi));
	}
}

double Sinus::get_phase() const
{
	return m_amplitude;
}

double Sinus::get_amplitude() const
{
	return m_amplitude;
}

void Sinus::set_phase(double new_phase)
{
	m_phase = new_phase;
	double phi = m_phase * M_PI / 180;
	for (int i = m_delay; i < m_values.get_size()[1]; i++) {
		int k = i - m_delay;
		phi = m_phase * M_PI / 180;
		m_values(0, i, m_amplitude * sin(2 * M_PI * m_frequency * k * m_Ts + phi));
	}
}

void Sinus::set_amplitude(double new_amplitude)
{
	m_amplitude = new_amplitude;
	for (int i = m_delay; i < m_values.get_size()[1]; i++) {
		int k = i - m_delay;
		double phi = m_phase * M_PI / 180;
		m_values(0, i, m_amplitude * sin(2 * M_PI * m_frequency * k * m_Ts + phi));
	}
}


int testSinus()
{
	Sinus s1;
	s1.printOn(std::cout);
	int duration = 100;
	double amplitude = 1.0;
	double frequency = 10;
	double Ts = 0.001;
	double phase = 0;
	int delay = 0;
	
	Sinus s2(duration , amplitude, frequency, Ts, phase, delay);
	s2.printOn(std::cout);
	s2.log("");

	return(0);
}
