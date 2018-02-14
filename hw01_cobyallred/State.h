#pragma once
class State
{
private:
	int jugAWater;
	int jugBWater;
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

	bool isStateGoal(State goalState);

	bool areStatesEqual(State compareState);

	std::string getStateString();
};

