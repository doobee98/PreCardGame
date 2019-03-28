#pragma once
#include <iostream>
#include <string>
#include "CardConfig.h"
#include "ConsoleConfig.h"
//#include "Field.h"
using namespace std;


class Card {
	const Trump t;
	const int number;
	const Attack atk_value;
	Card(Trump t, int num); // private constructor : factory
	friend class CardFactory;

public:
	Trump GetTrump() const;
	int GetNumber() const;
	Attack GetAtkValue() const;

//	bool CanUse(const Field& f) const;
	bool IsAtkCard() const;

private:
	bool CheckValid() const;
	Attack InitializeAtk(int num) const;

public:
	friend ostream& operator<<(ostream& os, const Card& c);
	bool operator<(const Card& other) const;
};

bool compare(Card* c1, Card* c2) { // 포인터형 비교
	if (c1->GetTrump() < c2->GetTrump())
		return true;
	else if (c1->GetTrump() > c2->GetTrump())
		return false;
	else
		return c1->GetNumber() < c2->GetNumber();
}



Card::Card(Trump t, int num) : t(t), number(num), atk_value(InitializeAtk(num)) {
	// 객체 초기화시 trump와 value가 valid한 조합인지 체크함
	if (CheckValid() == false)
		throw "Card / CheckValid: Invalid Card Pattern";
}


Trump Card::GetTrump() const { return t; }
int Card::GetNumber() const { return number; }
Attack Card::GetAtkValue() const { return atk_value; }




bool Card::CanUse(const Field& f) const{
	if (f.IsAttacking() == true && IsAtkCard() == false) 
		return false;
	

	if (f.GetLeadSuit() == Trump::JOKER || t == Trump::JOKER)
		return true;
	else
		return f.GetLeadSuit() == t || f.GetLeadNumber() == number;
}


bool Card::IsAtkCard() const {
	return atk_value != Attack::UNDEFINED;
}


bool Card::CheckValid() const {
	switch (t) {
	case Trump::JOKER:
		if (number != JOKER_NUM) return false;
		break;
	case Trump::MAX: return false;
	default: // 4 Pattern trump
		if (number < A || number > K) return false;
		break;
	}

	return true;
}


Attack Card::InitializeAtk(int num) const {
	switch (num) {
	case A: 
		return Attack::ACE;
	case 2: 
		return Attack::TWO;
	case JOKER_NUM:
		return Attack::JOKER;
	default:
		return Attack::UNDEFINED;
	}
}


ostream& operator<<(ostream& os, const Card& c) {
	switch (c.t){
	case Trump::JOKER:
		SETCOLOR(YELLOW);
		os << "JOKER";
		SETCOLOR();
		break;
	case Trump::HEART: case Trump::DIAMOND:
		SETCOLOR(LIGHTRED);
		os << PRINT_TRUMP(c.t) << " ";
		os.width(2); os.fill(' ');
		switch (c.number) {
		case A: os << "A"; break;
		case J: os << "J"; break;
		case Q: os << "Q"; break;
		case K: os << "K"; break;
		default: os << c.number; break;
		}
		SETCOLOR();
		break;
	case Trump::CLOVER: case Trump::SPADE:
		SETCOLOR(DARKGRAY);
		os << PRINT_TRUMP(c.t) << " ";
		os.width(2); os.fill(' ');
		switch (c.number) {
		case A: os << "A"; break;
		case J: os << "J"; break;
		case Q: os << "Q"; break;
		case K: os << "K"; break;
		default: os << c.number; break;
		}
		SETCOLOR();
		break;
	default:
		throw "Card / operator<< : Trump = MAX";
	}
	return os;
}

bool Card::operator<(const Card& other) const {
	if (t < other.GetTrump())
		return true;
	else if (t > other.GetTrump())
		return false;
	else 
		return number < other.GetNumber();
}