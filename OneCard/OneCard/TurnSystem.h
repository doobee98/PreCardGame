#pragma once
#include <deque>
#include "Player.h"

#define DPITER deque<Player*>::iterator

enum Direction {
	CLOCKWISE = 1, ANTICLOCKWISE = -1
};

class TurnSystem {
private:
	static TurnSystem* instance;
	Direction dir;
	int now_player_loc;
	int next_player_change;
	int max_player_num;

	TurnSystem();
	~TurnSystem();

public:
	static TurnSystem& GetInstance();
	Direction GetDirection() const;
	void SetMaxPlayerNum(int num);
	DPITER& NextPlayer(DPITER& iter);
	void PlayJ();
	void PlayQ();
	void PlayK();
	void PlayDefault();
	
private:
	void SetNextPlayerChange(int num);
};

TurnSystem* TurnSystem::instance = NULL;
TurnSystem& TurnSystem::GetInstance() {
	if (instance == NULL)
		instance = new TurnSystem();
	return *instance;
}


TurnSystem::TurnSystem(): dir(CLOCKWISE), now_player_loc(0), next_player_change(0), max_player_num(-1) {

}

TurnSystem::~TurnSystem() {}


Direction TurnSystem::GetDirection() const {
	return dir;
}


void TurnSystem::SetMaxPlayerNum(int num) {
	if (max_player_num != -1)
		throw "TurnSystem::SetMaxPlayerNum - Notice trying to reInitialize Max_Player_num";
	max_player_num = num;
	next_player_change = rand() % max_player_num; // random player start 
}


DPITER& TurnSystem::NextPlayer(DPITER& iter) {
	(**iter).SetNowTurn(false);
	if (next_player_change >= 0) {
		for (int i = 0; i < next_player_change; i++, ++iter);
	}
	else {
		for (int i = 0; i > next_player_change; i--, --iter);
	}

	(**iter).SetNowTurn(true);
	now_player_loc += next_player_change;
	next_player_change = 0;
	return iter;
}


void TurnSystem::PlayJ() {
	SetNextPlayerChange(2 * dir);
}

void TurnSystem::PlayQ() {
	dir = dir == CLOCKWISE ? ANTICLOCKWISE : CLOCKWISE;
	SetNextPlayerChange(1 * dir);
}

void TurnSystem::PlayK() {
	SetNextPlayerChange(0);
}

void TurnSystem::PlayDefault() {
	SetNextPlayerChange(1 * dir);
}

void TurnSystem::SetNextPlayerChange(int num) {
	if (next_player_change != 0)
		throw "TurnSystem::SetNextPlayerChange - Notice trying to change Next Player Location twice in one turn";

	if (now_player_loc + num < 0)
		SetNextPlayerChange(num + max_player_num);
	else if (now_player_loc + num >= max_player_num)
		SetNextPlayerChange(num - max_player_num);
	else
		next_player_change = num;
}