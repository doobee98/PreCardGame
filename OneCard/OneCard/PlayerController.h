#pragma once
#include "Player.h"
#ifndef interface
#define interface class
#endif

enum Action {
	HAND1, HAND2, HAND3, HAND4, HAND5, 
	HAND6, HAND7, HAND8, HAND9, HAND10,
	HAND11, HAND12, HAND13, HAND14, HAND15,
	DRAW = -1, SORT = -2, UNDEFINED = -100 // 1 <= HAND <= 15
};




interface PlayerController {
protected:
	// ref to Player.hand and Field.CanPlayCard

public:
	int SelectAction() const;
	bool ExclaimOneCard();

private:
	virtual int GetKey() const = 0;
};


int PlayerController::SelectAction() const { // 프로토. 실제 GetKey 설계후 다시 건드리기
	int key = GetKey();

	if (key == Action::DRAW)
		return Action::DRAW;
	else if (key == Action::SORT)
		return Action::SORT;
	else if (key >= 1 && key <= MAX_HAND) // USE HAND
		return key;
	else
		return SelectAction(); // 입력 오류시 다시 입력받음
}


bool PlayerController::ExclaimOneCard() {
	return false;
}


