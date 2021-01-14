#include "GUI.h"

const double M_PI = 3.14159265358979323846;

GUI::GUI()
{
}

// GUI LAUNCHER
int GUI::launch()
{

	// Software name and version
	std::cout << "**************************************" << std::endl;
	std::cout << "    _     ____  ____  _     ____ " << std::endl;
	std::cout << "   / \\ /|/  _ \\/  __\\/ \\ /\\/ ___\\ " << std::endl;
	std::cout << "   | |_||| / \\||  \\/|| | |||    \\ " << std::endl;
	std::cout << "   | | ||| \\_/||    /| \\_/|\\___ |" << std::endl;
	std::cout << "   \\_/ \\|\\____/\\_/\\_\\\\____/\\____/" << std::endl << std::endl;
	std::cout << "**************************************" << std::endl << std::endl;
	

	unsigned int choice = 0; // Number of the choosen functionnality

	m_H.recover_numerator(numerator_autosave);
	m_H.recover_denominator(denominator_autosave);
	m_H.recover_Ts(Ts_autosave);

	while (true) {
		m_H.log_numerator(numerator_autosave);
		m_H.log_denominator(denominator_autosave);
		m_H.log_Ts(Ts_autosave);

		std::cout << std::endl << std::endl << "Your transfer function is :" << std::endl << std::endl;
		m_H.printOn(std::cout); // Each time that the user return to the menu, the actual tf is displayed

		// Menu displaying
		std::cout << " ________________________________________ " << std::endl << std::endl;
		std::cout << "|///////////////// MENU /////////////////|" << std::endl;
		std::cout << "|                                        |" << std::endl;
		std::cout << "|	1- Enter a new transfer function |" << std::endl;
		std::cout << "|	2- Change your transfer function |" << std::endl;
		std::cout << "|	3- Serie function                |" << std::endl;
		std::cout << "|	4- Loop function                 |" << std::endl;
		std::cout << "|	5- State space representation    |" << std::endl;
		std::cout << "|	6- Stability analysis            |" << std::endl;
		std::cout << "|	7- Temporal response             |" << std::endl;
		std::cout << "|	8- Bode representation           |" << std::endl;
		std::cout << "|	9- Set Ts                        |" << std::endl;
		std::cout << "|	10- Previous                     |" << std::endl;
		std::cout << "|	OTHER - Exit                     |" << std::endl;
		std::cout << " ________________________________________ " << std::endl;
		std::cout << "What do you want to do ?" << std::endl;

		arrow();
		choice = input_int();

		// Launch the choiced functionality with a switch case
		try {
			switch (choice)
			{
			case 1:
				m_buf_prev.push(m_H);
				new_tf();
				break;
			case 2:
				m_buf_prev.push(m_H);
				change_tf();
				break;
			case 3:
				m_buf_prev.push(m_H);
				series_tf();
				break;
			case 4:
				m_buf_prev.push(m_H);
				loop_tf();
				break;
			case 5:
				ss();
				break;
			case 6:
				check_stability();
				break;
			case 7:
				simulation();
				break;
			case 8:
				bode_representation();
				break;
			case 9:
				m_buf_prev.push(m_H);
				Ts_setting();
				break;
			case 10:
				prev();
				break;
			default:
				return(0);
			}
		}

		catch (std::out_of_range const& e)
		{
			std::cerr << e.what() << std::endl;
		}

		catch (std::length_error const& e)
		{
			std::cerr << e.what() << std::endl;
		}

		catch (std::invalid_argument const& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

// Interface to create a new TF
void GUI::new_tf()
{
	double buf;
	int p;
	int n;
	Polynom N;
	Polynom D;

	std::cout << "Numerator degree :" << std::endl;
	arrow();
	p = input_int();
	for (int i = 0; i <= p; i++) {
		std::cout << "Coefficient of degree " << i << " :" << std::endl;
		arrow();
		buf = input_double();
		N.set_coef(i, buf);
	}

	std::cout << "Denominator degree :" << std::endl;
	arrow();
	n = input_int();
	for (int i = 0; i <= n; i++) {
		std::cout << "Coefficient of degree " << i << " :" << std::endl;
		arrow();
		buf = input_double();
		D.set_coef(i, buf);
	}

	m_H.set_numerator(N);
	m_H.set_denominator(D);
}

// Interface to change current TF
void GUI::change_tf()
{
	int degree;
	double new_coef;

	Polynom N;

	while (true) {
		std::cout << "Numerator : Enter the degree of the coefficient you want to change (enter a negative value to continue) :" << std::endl;
		arrow();
		degree = input_int();
		if (degree < 0)
			break;
		std::cout << "Enter the coefficient that you want :" << std::endl;
		arrow();
		new_coef = input_double();
		N = m_H.get_numerator();
		N.set_coef(degree, new_coef);
		m_H.set_numerator(N);
		std::cout << "Now your system is :" << std::endl;
		m_H.printOn(std::cout);
	}
	while (true) {
		std::cout << "Denominator : Enter the degree of the coefficient you want to change (enter a negative value to continue) :" << std::endl;
		arrow();
		degree = input_int();
		if (degree < 0)
			break;
		std::cout << "Enter the coefficient that you want :" << std::endl;
		arrow();
		new_coef = input_double();
		N = m_H.get_denominator();
		N.set_coef(degree, new_coef);
		m_H.set_denominator(N);
		std::cout << "Now your system is :" << std::endl;
		m_H.printOn(std::cout);
	}
}

void GUI::series_tf()
{
	std::cout << "Configure the function that you want in series with the current one :" << std::endl;

	TransferFunction H_serie;

	double buf;
	int p;
	int n;
	Polynom N;
	Polynom D;

	std::cout << "Numerator degree :" << std::endl;
	arrow();
	p = input_int();
	for (int i = 0; i <= p; i++) {
		std::cout << "Coefficient of degree " << i << " :" << std::endl;
		arrow();
		buf = input_double();
		N.set_coef(i, buf);
	}

	std::cout << "Denominator degree :" << std::endl;
	arrow();
	n = input_int();
	for (int i = 0; i <= n; i++) {
		std::cout << "Coefficient of degree " << i << " :" << std::endl;
		arrow();
		buf = input_double();
		D.set_coef(i, buf);
	}

	H_serie.set_numerator(N);
	H_serie.set_denominator(D);
	H_serie.set_Te(m_H.get_Te());

	m_H = m_H * H_serie;
}

void GUI::loop_tf()
{
	std::cout << "Configure the function that you want on the loop :" << std::endl;

	TransferFunction H_loop;

	double buf;
	int p;
	int n;
	Polynom N;
	Polynom D;
	
	Polynom u;
	u.set_coef(0,1);
	TransferFunction U;
	U.set_numerator(u);
	U.set_denominator(u);
	U.set_Te(m_H.get_Te());

	std::cout << "Numerator degree :" << std::endl;
	arrow();
	p = input_int();
	for (int i = 0; i <= p; i++) {
		std::cout << "Coefficient of degree " << i << " :" << std::endl;
		arrow();
		buf = input_double();
		N.set_coef(i, buf);
	}

	std::cout << "Denominator degree :" << std::endl;
	arrow();
	n = input_int();
	for (int i = 0; i <= n; i++) {
		std::cout << "Coefficient of degree " << i << " :" << std::endl;
		arrow();
		buf = input_double();
		D.set_coef(i, buf);
	}
	H_loop.set_numerator(N);
	H_loop.set_denominator(D);
	H_loop.set_Te(m_H.get_Te());

	m_H = m_H / (U + m_H * H_loop);
}

// Interface to convert the TF to a SS
void GUI::ss()
{
	Ss ss;
	ss = m_H.tf2ss();
	ss.printOn(std::cout);
}

// Interface to check the stability of the system
void GUI::check_stability()
{
	std::cout << std::endl;
	Matrix jarray = m_H.JArray();
	std::cout << std::endl << "Jury's array :" << std::endl;
	jarray.printJOn(std::cout);
}

// Interface to generate the temporal response to a signal (ramp, sinus or step)
void GUI::simulation()
{
	int choice = 0;

		int n = m_H.get_denominator().get_degree();
		Matrix x0(n, 1);

		double buf;
		for (int i = 0; i < n; i++) {
			std::cout << "Enter initial condition on x" << i << std::endl;
			arrow();
			buf = input_double();
			x0(i, 0, buf);
		}

		std::cout << "Choose your entry :" << std::endl << std::endl;
		std::cout << "1- Step" << std::endl;
		std::cout << "2- Ramp" << std::endl;
		std::cout << "3- Sinus" << std::endl;
		do {
			arrow();
			choice = input_int();

			if (choice == 1) {
			
				int duration;
				double amplitude;
				int delay;

				std::cout << "Duration :" << std::endl;
				arrow();
				duration = input_int();
				std::cout << "Amplitude :" << std::endl;
				arrow();
				while (!(std::cin >> amplitude)) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input type, please retry" << std::endl;
					arrow();
				}
				std::cout << "Delay :" << std::endl;
				arrow();
				delay = input_int();

				Step s(duration, amplitude, delay, m_H.get_Te());
				do {
					std::cout << "Do you want to log the result (1 : Yes, 0 : No) ? (it's going to overwrite previous backup)" << std::endl;
					arrow();
					buf = input_int();
					if (buf == 1) {
						s.log(input);
						m_H.simulation(s, x0).log(output);
					}
					else if (buf == 0)
						std::cout << "Results not saved" << std::endl;
				} while ( !(buf == 0 || buf == 1) );
				break;
			}
			if (choice == 2) {
				int duration;
				double slope;
				int delay;

				std::cout << "Duration :" << std::endl;
				arrow();
				duration = input_int();
				std::cout << "Slope :" << std::endl;
				arrow();
				slope = input_double();
				std::cout << "Delay :" << std::endl;
				arrow();
				delay = input_int();
				Ramp r(duration, slope, delay, m_H.get_Te());
				do {
					std::cout << "Do you want to log the result (1 : Yes, 0 : No) ? (it's going to overwrite previous backup)" << std::endl;
					arrow();
					buf = input_int();
					if (buf == 1) {
						r.log(input);
						m_H.simulation(r, x0).log(output);
					}
					else if (buf == 0)
						std::cout << "Results not saved" << std::endl;
				} while (!(buf == 0 || buf == 1));
				break;
			}
			if (choice == 3) {
				int duration;
				double amplitude;
				double frequency;
				double phase;
				int delay;

				std::cout << "Duration :" << std::endl;
				arrow();
				duration = input_int();
				std::cout << "Amplitude :" << std::endl;
				arrow();
				amplitude = input_double();
				std::cout << "Frequency :" << std::endl;
				arrow();
				frequency = input_double();
				std::cout << "Phase :" << std::endl;
				arrow();
				phase = input_double();;
				std::cout << "Delay :" << std::endl;
				arrow();
				delay = input_int();
				Sinus r(duration, amplitude, frequency, m_H.get_Te(), phase, delay);

				do {
					std::cout << "Do you want to log the result (1 : Yes, 0 : No) ? (it's going to overwrite previous backup)" << std::endl;
					arrow();
					buf = input_int();
					if (buf == 1) {
						m_H.simulation(r, x0).log(output);
						r.log(input);
					}
					else if (buf == 0)
						std::cout << "Results not saved" << std::endl;
				} while (!(buf == 0 || buf == 1));

				break;
			}
		
	}while (choice < 1 || choice>3);
}

// Interface to generate the Bode representation
void GUI::bode_representation()
{
	double w_max;
	double w_min;
	std::cout << "w_max :"<<std::endl;
	do {
		arrow();
		w_max = input_double();
		if (w_max > M_PI / m_H.get_Te())
			std::cout << "The max pulsation must be smaller than pi/Ts" << std::endl;
		else
			break;
	} while (true);

	std::cout << "w_min :" << std::endl;
	arrow();
	w_min = input_double();

	std::cout << "Number of points :" << std::endl;
	arrow();
	int nb_point = input_int();

	Matrix mod = m_H.bode_module(w_min, w_max, nb_point);
	Matrix arg = m_H.bode_argument(w_min, w_max, nb_point);
	
	int buf;
	do {
		std::cout << "Do you want to log the result (1 : Yes, 0 : No) ? (it's going to overwrite previous backup)" << std::endl;
		arrow();
		buf = input_int();
		if (buf == 1) {
			mod.log(bode_mod);
			arg.log(bode_arg);
		}
		else if (buf == 0)
			std::cout << "Results not saved" << std::endl;
	} while (!(buf == 0 || buf == 1));

}

// Interface to set Ts
void GUI::Ts_setting()
{
	double new_Ts;
	std::cout << "Enter a new Ts :" << std::endl;
	arrow();
	while (true) {
		new_Ts = input_double();
		if (new_Ts > 0)
			break;
		else {
			std::cout<<"Ts must be positive"<<std::endl;
			arrow();
		}
	}
	m_H.set_Te(new_Ts);
}

void GUI::arrow()
{
	std::cout << "=> ";
}

int GUI::input_int()
{
	int buf;
	while (!(std::cin >> buf)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input type, please retry" << std::endl;
		arrow();
	}
	return buf;
}

double GUI::input_double()
{
	double buf;
	while (!(std::cin >> buf)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input type, please retry" << std::endl;
		arrow();
	}
	return buf;
}

void GUI::prev()
{
	if (!(m_buf_prev.isEmpty())) {
		TransferFunction H_prev = m_buf_prev.top();
		m_H = H_prev;
		m_buf_prev.pop();
	}
}

