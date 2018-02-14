/*
* ECE 479 Homework #1
* Coby Allred
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Execute.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Usage: hw01_allred inputFile" << std::endl;
		return EXIT_FAILURE;
	}

	// create the execute class with the input and output
	Execute programExecute = Execute(argv[1], argv[2]);

	// start the output file
	programExecute.createOutput();

	if (programExecute.getInitValues() == true) {

	}
	else {
		std::cout << "Error getting input values. Please specify a valid input file." << std::endl;
		return EXIT_FAILURE;
	}

	// execute the random strategy
	programExecute.runStrategy('A');

	// execute the systematic strategy
	programExecute.runStrategy('B');

	// close the output file
	programExecute.closeOutput();

	return EXIT_SUCCESS;
}