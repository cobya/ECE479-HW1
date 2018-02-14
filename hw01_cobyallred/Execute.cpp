#include "Execute.h"

// Get the intial values of the problem from the input file
bool Execute::getInitValues()
{
	inputFile.open(inputFileName); // Opens the file

	if (inputFile.is_open()) { // If open, get lines
		std::string inputLine;
		int jugAValue, jugBValue;

		// get A capacity
		getline(inputFile, inputLine, ':');
		getline(inputFile, inputLine);
		std::istringstream(inputLine) >> jugAValue;
		jugAVolume = jugAValue;
		jugAName = std::to_string(jugAVolume) + "-gallon jug";

		// get B capacity
		getline(inputFile, inputLine, ':');
		getline(inputFile, inputLine);
		std::istringstream(inputLine) >> jugBValue;
		jugBVolume = jugBValue;
		jugBName = std::to_string(jugBVolume) + "-gallon jug";

		// get init values
		getline(inputFile, inputLine, ':');
		getline(inputFile, inputLine);
		std::stringstream initStateLine(inputLine);
		initStateLine >> jugAValue;
		initStateLine >> jugBValue;

		// set initial state
		initialState = State(jugAValue, jugBValue);

		// get goal values
		getline(inputFile, inputLine, ':');
		getline(inputFile, inputLine);
		std::stringstream goalStateLine(inputLine);
		goalStateLine >> jugAValue;
		goalStateLine >> jugBValue;

		// set goal state
		goalState = State(jugAValue, jugBValue);
	}
	else {
		return false; // False to exit program
	}

	return true;
}

// check if a rule you want to use is valid
bool Execute::isRuleValid(State checkState, int rule)
{
	switch (rule) {
	case 1:
		// Fill A
		if (checkState.getJugAWater() < this->jugAVolume) {
			return true;
		}
		return false;
	case 2:
		// Fill B
		if (checkState.getJugBWater() < this->jugBVolume) {
			return true;
		}
		return false;
	case 3:
		// Pour only some, always false
		return false;
	case 4:
		// Pour only some, always false
		return false;
	case 5:
		// Empty A
		if (checkState.getJugAWater() > 0) {
			return true;
		}
		return false;
	case 6:
		// Empty B
		if (checkState.getJugBWater() > 0) {
			return true;
		}
		return false;
	case 7:
		// A to B
		if ((checkState.getSumOfJugs() >= this->jugAVolume) && (checkState.getJugAWater() < this->jugAVolume)) {
			return true;
		}
		return false;
	case 8:
		// B to A
		if ((checkState.getSumOfJugs() >= this->jugBVolume) && (checkState.getJugBWater() < this->jugBVolume)) {
			return true;
		}
		return false;
	case 9:
		// A to B until empty
		if ((checkState.getSumOfJugs() <= this->jugAVolume) && (checkState.getJugBWater() > 0)) {
			return true;
		}
		return false;
	case 10:
		// B to A until empty
		if ((checkState.getSumOfJugs() <= this->jugBVolume) && (checkState.getJugAWater() > 0)) {
			return true;
		}
		return false;
	default:
		return false;
	}
}

// use a rule on the current state
std::string Execute::useRule(int rule)
{
	std::string writeString;
	switch (rule) {
	case 1:
		currentState.setJugWaters(this->jugAVolume, currentState.getJugBWater());
		writeString = "Fill the " + this->jugAName + "\t\t\t\t\t";
		break;
	case 2:
		currentState.setJugWaters(currentState.getJugAWater(), this->jugBVolume);
		writeString = "Fill the " + this->jugBName + "\t\t\t\t\t";
		break;
	case 5:
		currentState.setJugWaters(0, currentState.getJugBWater());
		writeString = "Empty the " + this->jugAName + "\t\t\t\t\t";
		break;
	case 6:
		currentState.setJugWaters(currentState.getJugAWater(), 0);
		writeString = "Empty the " + this->jugBName + "\t\t\t\t\t";
		break;
	case 7:
		currentState.setJugWaters(this->jugAVolume, currentState.getSumOfJugs() - this->jugAVolume);
		writeString = "Pour water from " + this->jugBName + " into " + this->jugAName + "\t\t";
		break;
	case 8:
		currentState.setJugWaters(currentState.getSumOfJugs() - this->jugBVolume, this->jugBVolume);
		writeString = "Pour water from " + this->jugAName + " into " + this->jugBName + "\t\t";
		break;
	case 9:
		currentState.setJugWaters(currentState.getSumOfJugs(), 0);
		writeString = "Pour water from " + this->jugBName + " into " + this->jugAName + "\t\t";
		break;
	case 10:
		currentState.setJugWaters(0, currentState.getSumOfJugs());
		writeString = "Pour water from " + this->jugAName + " into " + this->jugBName + "\t\t";
		break;
	default:
		return "Error, invalid rule # used.";
	}

	return writeString + "--- state: " + currentState.getStateString();
}

// return a new state based on a given rule
State Execute::checkRuleOutcome(State checkState, int rule) {
	// switch based on rule and update the checkState
	switch (rule) {
	case 1:
		checkState.setJugWaters(this->jugAVolume, checkState.getJugBWater());
		break;
	case 2:
		checkState.setJugWaters(checkState.getJugAWater(), this->jugBVolume);
		break;
	case 5:
		checkState.setJugWaters(0, checkState.getJugBWater());
		break;
	case 6:
		checkState.setJugWaters(checkState.getJugAWater(), 0);
		break;
	case 7:
		checkState.setJugWaters(this->jugAVolume, checkState.getSumOfJugs() - this->jugAVolume);
		break;
	case 8:
		checkState.setJugWaters(checkState.getSumOfJugs() - this->jugBVolume, this->jugBVolume);
		break;
	case 9:
		checkState.setJugWaters(checkState.getSumOfJugs(), 0);
		break;
	case 10:
		checkState.setJugWaters(0, checkState.getSumOfJugs());
		break;
	default:
		break;
	}

	return checkState;
}

// Run a specified strategy
void Execute::runStrategy(char strategyType)
{
	// if running a random strategy
	if (strategyType == 'A') {
		// seed our random values and initial state
		srand((int)time(NULL));
		currentState = initialState.copyState();

		// initial prints
		outputString("Strategy A");
		outputString("Starting out with " + this->jugAName + " and a " + this->jugBName + "\t--- state: " + currentState.getStateString());

		// while we are not in the goal state and less than 250 tries
		int randomTries = 0;
		while ((currentState.isGoalState(goalState) == false) && (randomTries < 250)) {
			// get a random rule
			int randomRule = (rand() % 10) + 1;

			// while the rule won't work, get a new one
			while (isRuleValid(currentState, randomRule) == false) {
				randomRule = (rand() % 10) + 1;
			}

			// We have a valid rule, so apply it
			std::string ruleMessage = useRule(randomRule);
			outputString(ruleMessage);

			// increment tries
			randomTries++;
		}

		// if we hit the limit, say so
		if (randomTries == 250) {
			outputString("No solution found. Strategy A terminated.");
		}

		// newline between strategies
		outputString("");

		return;
	}
	else if (strategyType == 'B') {
		// get our initial state
		currentState = initialState.copyState();

		// initial prints
		outputString("Strategy B");
		outputString("Starting out with " + this->jugAName + " and a " + this->jugBName + "\t--- state: " + currentState.getStateString());

		// find our node path
		std::stack<State> pathStates = DFS(currentState, goalState);

		// print node path
		if (pathStates.empty() == false) {
			std::stack<State> toPrint;

			while (pathStates.empty() == false) {
				State pathToPrint = pathStates.top();
				toPrint.push(pathToPrint);
				pathStates.pop();
			}

			// print them now
			toPrint.pop(); // remove extra init state
			while (toPrint.empty() == false) {
				
				State pathToPrint = toPrint.top();

				// with how our algorithm works, goal state can print -1, which is bad
				int jugOneWater = pathToPrint.getJugAWater();
				int jugTwoWater = pathToPrint.getJugBWater();
				if (jugOneWater == -1) {
					pathToPrint.setJugWaters(0, jugTwoWater);
				}
				else if (jugTwoWater == -1) {
					pathToPrint.setJugWaters(jugOneWater, 0);
				}

				// find which rule was used and print its message
				std::vector<int> possibleRules = getNextRulesForState(currentState);
				int ruleUsed = 0;
				for (int i = 1; i <= 10; i++) {
					State ruleOutcome = checkRuleOutcome(currentState, i);
					if (ruleOutcome.areStatesEqual(pathToPrint) == true) {
						ruleUsed = i;
						break;
					}
				}
				std::string ruleMessage = useRule(ruleUsed);
				outputString(ruleMessage);

				toPrint.pop();
			}
		}
		else {
			outputString("No solution found. Strategy B terminated.");
		}

		return;
	}
}

std::stack<State> Execute::DFS(State initialState, State goalState) {
	std::stack<State> path; // path to target
	std::vector<State> visitedStates; // visited
	std::vector<State> adjacentStates;

	State searchState = initialState;
	while (searchState.isGoalState(goalState) == false) {
		adjacentStates = getNextStatesForState(searchState);

		bool foundNonVisited = false;
		// search adjacent nodes
		for (int i = 0; (unsigned)i < adjacentStates.size(); i++) {

			// search for a similar node already visited
			bool foundAdjInVisited = false;
			for (int j = 0; (unsigned)j < visitedStates.size(); j++) {
				if (visitedStates.at(j).areStatesEqual(adjacentStates.at(i)) == true) {
					foundAdjInVisited = true;
				}
			}

			// if adj not in visited, push to path
			if (foundAdjInVisited == false) {
				path.push(searchState);
				visitedStates.insert(visitedStates.begin(), adjacentStates.at(i));
				searchState = adjacentStates.at(i);
				foundNonVisited = true;
				break;
			}
		}

		if (foundNonVisited) {
			continue;
		}

		if (path.empty()) {
			return path;
		}
		
		searchState = path.top();
		path.pop();
	}

	path.push(goalState);
	return path;
}

// get applicable next states
std::vector<State> Execute::getNextStatesForState(State checkState) {
	std::vector<State> validRules;

	for (int i = 1; i <= 10; i++) {
		if (isRuleValid(checkState, i) == true) {
			validRules.push_back(checkRuleOutcome(checkState, i));
		}
	}

	return validRules;
}

std::vector<int> Execute::getNextRulesForState(State checkState)
{
	std::vector<int> validRules;

	for (int i = 1; i <= 10; i++) {
		if (isRuleValid(checkState, i) == true) {
			validRules.push_back(i);
		}
	}

	return validRules;
}

// Start the output stream
bool Execute::createOutput()
{
	outputFile.open("output.txt"); // Opens the file

	if (outputFile.is_open()) { // If open, get lines
		return true;
	}
	else {
		return false; // False to exit program
	}
}

// Send a string of output text
void Execute::outputString(std::string outputText)
{
	std::cout << outputText << std::endl;
	outputFile << outputText << std::endl;
}

// Close the output file stream
void Execute::closeOutput()
{
	outputFile.close();
}
