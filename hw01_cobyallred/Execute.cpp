#include "Execute.h"

bool Execute::getInitValues()
{
	std::string inputLine;

	inputFile.open(inputFileName); // Opens the file

	if (inputFile.is_open()) { // If open, get lines
		while (getline(inputFile, inputLine)) {
			std::string user, follower, shouldBeNothing; // Temp strings

			istringstream inputParsing(inputLine); // Parsing the input
			inputParsing >> user;
			inputParsing >> follower;
			inputParsing >> shouldBeNothing;

			if (isUsernameValid(user) == true && isUsernameValid(follower) == true && shouldBeNothing.empty() == true) { // If usernames are valid, continue
				for (int i = 0; (unsigned)i < user.size(); i++) { // Remove and return / newline chars
					if (user.at(i) == '\r' || user.at(i) == '\n') {
						user.erase(user.at(i));
					}
				}
				for (int i = 0; (unsigned)i < follower.size(); i++) { // Remove and return / newline chars
					if (follower.at(i) == '\r' || follower.at(i) == '\n') {
						user.erase(follower.at(i));
					}
				}

				addInputLine(user, follower); // Adds the user using the above function
			}
			else {
				this->inputGraph.setValid(false);
				return true; // Returns true since it must create empty output
			}
		}
	}
	else {
		return false; // False to exit program
	}

	return true;
}

void Execute::runStrategy(std::string strategyType)
{
	if (strategyType.compare("random") == 0) {

	}
	else if (strategyType.compare("systematic") == 0) {

	}
}


Execute::~Execute()
{
}
