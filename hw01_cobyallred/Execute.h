#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <ctime>
#include "State.h"

class Execute
{
private:
	// Input and Output variables
	char* inputFileName;
	char* outputFileName;
	FILE* inputFile;
	FILE* outputFile;

	// Problem variables
	int jugAVolume;
	int jugBVolume;
	std::string jugAName;
	std::string jugBName;
	State initialState;
	State currentState;
	State goalState;

public:
	Execute();
	Execute(char* inFileName, char* outFileName);

	bool getInitValues();

	bool isRuleValid(State checkState, int rule);

	std::string useRule(int rule);

	State checkRuleOutcome(State checkState, int rule);

	void runStrategy(char strategyType);

	std::stack<State> DFS(State initialState, State goalState);

	std::vector<State> getNextStatesForState(State checkState);

	std::vector<int> getNextRulesForState(State checkState);

	bool createOutput();

	void outputString(std::string outputText);

	void closeOutput();
};