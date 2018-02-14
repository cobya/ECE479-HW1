#include "State.h"
#include <iostream>
#include <fstream>

bool State::isStateGoal(State goalState)
{
	if ((goalState.getJugAWater() != -1) && (goalState.getJugAWater() != jugAWater)) {
		return false;
	}

	if ((goalState.getJugBWater() != -1) && (goalState.getJugBWater() != jugBWater)) {
		return false;
	}

	return true;
}

bool State::areStatesEqual(State compareState)
{
	if ((compareState.getJugAWater() == jugAWater) && (compareState.getJugBWater() == jugBWater)) {
		return true;
	}
	else {
		return false;
	}
}

std::string State::getStateString()
{
	std::string returnString = "(" + jugAWater + ',' + jugBWater + ')';
	return returnString;
}
