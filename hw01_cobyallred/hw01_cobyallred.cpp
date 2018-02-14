/*
* ECE 479 Homework #1
* Coby Allred
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Execute.h"

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage: hw01_allred inputFile outputFile");
		return EXIT_FAILURE;
	}

	// create the execute class with the input and output
	Execute programExecute = Execute(argv[1], argv[2]);

	if (programExecute.getInitValues() == true) {

	}
	else {
		printf("Error getting input values. Please specify a valid input file.");
	}

	// execute the random strategy
	programExecute.runStrategy("random");

	// execute the systematic strategy
	programExecute.runStrategy("systematic");

	return EXIT_SUCCESS;
}