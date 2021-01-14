#ifndef GUI_H
#define GUI_H

#include <iostream>
#include "TransferFunction.h"
#include"LIFO_TF.h"

class GUI {
private:
	TransferFunction m_H; // Current transfer function 
	LIFO_TF m_buf_prev; // Buffer for the prev() function

	/////////////// Chemins d'enregistrement ///////////////
	const char* numerator_autosave = "DATA/autosave_n.txt";
	const char* denominator_autosave = "DATA/autosave_d.txt";
	const char* Ts_autosave = "DATA/autosave_Ts.txt";
	const char* output = "DATA/output.txt";
	const char* input = "DATA/input.txt";
	const char* bode_arg = "DATA/bode_arg.txt";
	const char* bode_mod = "DATA/bode_mod.txt";

public:
	GUI(); // GUI constuctor
	int launch(); // GUI LAUNCHER

protected:

	virtual void new_tf(); // Interface to create a new TF
	virtual void change_tf(); // Interface to change current TF
	virtual void series_tf(); // Multiply current TF with another one
	virtual void loop_tf(); // Close loop with a tf
	virtual void ss(); // Interface to convert the TF to a SS
	virtual void check_stability(); // Interface to check the stability of the system
	virtual void simulation(); // Interface to generate the temporal response to a signal (ramp, sinus or step)
	virtual void bode_representation(); // Interface to generate the Bode representation
	virtual void Ts_setting(); // Interface to set Ts
	virtual void prev(); // Enable to go back to the previous system (Actually 10 systems in the LIFO)

	virtual void arrow(); // Print an arrow
	virtual int input_int(); // Log and check an int input
	virtual double input_double(); // Log and check a double input
};

#endif

