#pragma once
#include <iostream>
#include "CardConfig.h"
#include "ConsoleConfig.h"
#include "IPrint.h"
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
	void Print(int x, int y) const;

private:
	bool CheckValid() const;

	//friend ostream& operator<<(ostream& os, const Card& c);
};

bool compare(const Card* c1, const Card* c2) { // 포인터형 비교
	if (c1->GetTrump() < c2->GetTrump())
		return true;
	else if (c1->GetTrump() > c2->GetTrump())
		return false;
	else
		return c1->GetNumber() < c2->GetNumber();
}




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


void Card::Print(int x, int y) const {
	switch (trp) {
	case JOKER_TRP:
		ConsoleConfig::SetColor(Color::YELLOW);
		ConsoleConfig::XYPrint(x, y, "JOKER");
		ConsoleConfig::SetColor();
		return;

	case HEART: case DIAMOND:
		ConsoleConfig::SetColor(Color::LIGHTRED); break;
	case SPADE: case CLOVER:
		ConsoleConfig::SetColor(Color::DARKGRAY); break;
	}

	ConsoleConfig::XYPrint(x, y, CardConfig::TrumpToString(trp));


	switch (num) {
	case A: ConsoleConfig::XYPrint(x + 4, y, "A"); break;
	case J: ConsoleConfig::XYPrint(x + 4, y, "J"); break;
	case Q: ConsoleConfig::XYPrint(x + 4, y, "Q"); break;
	case K: ConsoleConfig::XYPrint(x + 4, y, "K"); break;
	case 10: ConsoleConfig::XYPrint(x + 3, y, "10"); break;
	default: ConsoleConfig::XYPrint(x + 4, y, to_string(num)); break;
	}

	ConsoleConfig::SetColor();
}
/*
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

*/