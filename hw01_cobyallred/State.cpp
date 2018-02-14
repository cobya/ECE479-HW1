#include "State.h"

// check if a state is equal to a goal state
bool State::isGoalState(State goalState)
{
	if ((goalState.getJugAWater() != -1) && (goalState.getJugAWater() != jugAWater)) {
		return false;
	}

	if ((goalState.getJugBWater() != -1) && (goalState.getJugBWater() != jugBWater)) {
		return false;
	}

	return true;
}

// check if two states are equal
bool State::areStatesEqual(State compareState)
{
	if ((compareState.getJugAWater() == jugAWater) && (compareState.getJugBWater() == jugBWater)) {
		return true;
	}
	else {
		return false;
	}
}

// return a string of the state
std::string State::getStateString()
{
	std::string returnString = "(" + std::to_string(jugAWater) + "," + std::to_string(jugBWater) + ")";
	return returnString;
}