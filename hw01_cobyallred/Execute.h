#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "State.h"
#include "Rules.h"
#include "Random.h"
#include "Systematic.h"

class Execute
{
private:
	char* inputFileName; // Input filename
	std::ifstream inputFile; // Input filestream
	char* outputFileName; // Output filename
	std::ofstream outputFile; // Output filestream

	int jugAVolume;
	int jugBVolume;
	State initialState;
	State goalState;

public:
	Execute() {
		inputFileName = NULL;
		outputFileName = NULL;
	}

	Execute(char* inFileName, char* outFileName) {
		inputFileName = inFileName;
		outputFileName = outFileName;
	}

	bool getInitValues();

	void runStrategy(std::string strategyType);
};

