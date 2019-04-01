#pragma once
#include <iostream>
#include "CardConfig.h"
#include "ConsoleConfig.h"
using namespace std;


class Card {
private:
	const Trump trp;
	const Number num;
	const Attack atk;

public:
	Card(Trump t, Number n);
	Trump GetTrump() const;
	Number GetNumber() const;
	Attack GetAttack() const;

private:
	bool CheckValid() const;

	friend ostream& operator<<(ostream& os, const Card& c);
};




Card::Card(Trump t, Number n) : trp(t), num(n), atk(CardConfig::NumToAtk(num)){
	if (CheckValid() != true)
		throw "Card::Card - Initialization Error";
}

Trump Card::GetTrump() const { return trp; }
Number Card::GetNumber() const { return num; }
Attack Card::GetAttack() const { return atk; }

bool Card::CheckValid() const {
	// because if init atk method, we don't check ATK
	if (trp == JOKER_TRP) 
		return num == JOKER_NUM;
	else 
		return num != JOKER_NUM;
}

ostream& operator<<(ostream& os, const Card& c) {
	switch (c.trp) {
	case JOKER_TRP:
		ConsoleConfig::SetColor(Color::YELLOW);
		os << "JOKER";
		ConsoleConfig::SetColor();
		return os;

	case HEART: case DIAMOND:
		ConsoleConfig::SetColor(Color::LIGHTRED); break;
	case SPADE: case CLOVER:
		ConsoleConfig::SetColor(Color::DARKGRAY); break;
	}

	os << CardConfig::TrumpToString(c.trp);
	os << " ";
	os.width(2); os.fill(' ');
	switch (c.num) {
	case A: os << "A"; break;
	case J: os << "J"; break;
	case Q: os << "Q"; break;
	case K: os << "K"; break;
	default: os << c.num; break;
	}
	ConsoleConfig::SetColor();
	return os;
}