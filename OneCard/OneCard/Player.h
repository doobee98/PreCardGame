#pragma once
#include "Card.h"
#include "IPrint.h"

#ifndef interface
#define interface class
#endif


interface Player : public IPrint {
private:
	bool now_turn;

public:
	Player();
	void Draw(int num);
//	virtual Key SelectAction() const = 0;
	void Print(int x, int y) const;
};

Player::Player() : now_turn(false) {

}

void Player::Draw(int num) {

}

void Player::Print(int x, int y) const {
	ConsoleConfig::XYPrint(x, y, "Player");
	ConsoleConfig::XYPrint(x, y + 1, "HELLO");
}