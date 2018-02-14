/*
* Define the various attributes of a state and allow updating it.
*/

#pragma once
#include <string>

class State
{
private:
	int jugAWater;
	int jugBWater;
	std::string jugAName;
	std::string jugBName;

public:
	State() {
		jugAWater = 0;
		jugBWater = 0;
	}

	State(int aWater, int bWater) {
		jugAWater = aWater;
		jugBWater = bWater;
	}


	int getJugAWater() {
		return jugAWater;
	}

	int getJugBWater() {
		return jugBWater;
	}

	int getSumOfJugs() {
		return jugAWater + jugBWater;
	}

	void setJugWaters(int jugANew, int jugBNew) {
		jugAWater = jugANew;
		jugBWater = jugBNew;
		return;
	}

	State copyState() {
		return State(jugAWater, jugBWater);
	}

	bool isGoalState(State goalState);

	bool areStatesEqual(State compareState);

	std::string getStateString();
};

