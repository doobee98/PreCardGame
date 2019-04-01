#pragma once
#include <deque>
#include "Player.h"

#define DPITER deque<Player>::iterator

enum Direction {
	CLOCKWISE, ANTICLOCKWISE
};

class TurnSystem {
private:
	static TurnSystem* instance;
	Direction dir;

	TurnSystem();
	~TurnSystem();

public:
	static TurnSystem& GetInstance();
	DPITER NextPlayer(DPITER iter); // how to choose next? iter? int number?
	
};

TurnSystem* TurnSystem::instance = NULL;
TurnSystem& TurnSystem::GetInstance() {
	if (instance == NULL)
		instance = new TurnSystem();
	return *instance;
}


TurnSystem::TurnSystem(): dir(CLOCKWISE) {

}

TurnSystem::~TurnSystem() {}

