/*
DEV : Samuel DONATO
Version : 4.0 (Final version)
Additional function : Previous
*/

#include <iostream>
#include "Polynom.h"
#include "TransferFunction.h"
#include "Matrix.h"
#include "Ss.h"
#include "Step.h"
#include "Ramp.h"
#include "Sinus.h"
#include "GUI.h"
#include "Complex.h"
#include "LIFO_TF.h"


int main()
{
	try {
		//testSs();
		//testMatrix();
		//testPolynom();
		//testTransfer();
		//testStep();
		//testTriangle();
		//testSinus();
		//testComplex();
		//test_LIFO_TF();
		GUI my_gui;
		my_gui.launch();
	}

	catch (std::out_of_range const& e)
	{
		std::cerr << e.what() << std::endl;
		return(1);
	}

	catch (std::length_error const& e)
	{
		std::cerr << e.what() << std::endl;
		return(1);
	}

	catch (std::invalid_argument const& e)
	{
		std::cerr << e.what() << std::endl;
		return(1);
	}
}

