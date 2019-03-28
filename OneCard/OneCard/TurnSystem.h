#pragma once
#include <iostream>
#include "IGetOpenCard.h"

enum Direction {
	CLOCK = 1, ANTICLOCK = -1
};


class TurnSystem {
	static TurnSystem* instance; 
private:
	int now_player_loc;
	int next_player_loc;
	const int player_num;
	Direction turn_direction;


	TurnSystem(int num);

public:
	static TurnSystem& GetInstance(int num);
	int NextPlayer(IGetOpenCard& ref_field);

private:
	void ReadyForNextTurn();
	void SetNext(int num);
	void JumpTurn();
	void ReverseTurn();
	void RepeatTurn();
};




TurnSystem* TurnSystem::instance = NULL;
TurnSystem& TurnSystem::GetInstance(int num) {
	if (instance == NULL) {
		instance = new TurnSystem(num);
	}
	return *instance;
}


TurnSystem::TurnSystem(int num) : player_num(num) {
	now_player_loc = 0;
	turn_direction = CLOCK;
	next_player_loc = 1;
}



int TurnSystem::NextPlayer(IGetOpenCard& ref_field) {
	switch ((ref_field.GetTopCard())->GetNumber()) {
	case J: JumpTurn(); break;
	case Q: ReverseTurn(); break;
	case K: RepeatTurn(); break;
	default: break;
	}
	int temp = next_player_loc;
	ReadyForNextTurn();
	return temp;
}



void TurnSystem::ReadyForNextTurn() {
	now_player_loc = next_player_loc;
	SetNext(now_player_loc + turn_direction);
}


void TurnSystem::SetNext(int num) {
	if (num < 0) {
		SetNext(player_num - num);
	}
	else if (num >= player_num) {
		SetNext(num - player_num);
	}
	else
		next_player_loc = num;
}



void TurnSystem::JumpTurn() {
	SetNext(now_player_loc + 2 * turn_direction);
}

void TurnSystem::ReverseTurn() {
	turn_direction = (turn_direction == CLOCK) ? ANTICLOCK : CLOCK;
	SetNext(now_player_loc + turn_direction);
}

void TurnSystem::RepeatTurn() {
	SetNext(now_player_loc);
}