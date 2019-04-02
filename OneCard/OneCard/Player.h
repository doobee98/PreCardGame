#pragma once
#include <deque>
#include <algorithm>
#include "Card.h"
#include "Field.h"
#include "IPrint.h"
#include "IDrawTop.h"

#ifndef interface
#define interface class
#endif

enum Action {
	HAND1, HAND2, HAND3, HAND4, HAND5, HAND6, HAND7, HAND8, HAND9, HAND10,
	HAND11, HAND12, HAND13, HAND14, HAND15, DRAW, SORT, ACT_UNDEFINED
};


interface Player : public IPrint {
private:
	string name;
	deque<const Card*> hand;
	bool now_turn;
	IDrawTop& ref_deck;

public:
	Player(string name, IDrawTop& deck);
	const string& GetName() const;
	void Draw(int num);
	const Card* PopHandCard(int num);
	void SortHand();
	const deque<const Card*>& GetHand() const;
	virtual Action SelectAction(const Field& ref_field) const = 0;
	virtual Trump SelectSevenEvent() = 0;
	void SetNowTurn(bool value);
	void Print(int x, int y) const;
};





Player::Player(string name, IDrawTop& deck) : name(name), hand(), now_turn(false), ref_deck(deck) {

}

const string& Player::GetName() const { return name; }

void Player::Draw(int num) {
	for (int i = 0; i < num; i++)
		hand.push_back(ref_deck.DrawTop());
}


const Card* Player::PopHandCard(int num) {
	const Card* temp = hand.at(num);
	hand.erase(hand.begin() + num);
	return temp;
}

void Player::SortHand() {
	sort(hand.begin(), hand.end(), compare);
}


const deque<const Card*>& Player::GetHand() const {
	return hand;
}


void Player::SetNowTurn(bool value) {
	now_turn = value;
}

void Player::Print(int x, int y) const {
	string hand_size_string = to_string(hand.size());
	if (hand.size() < 10) hand_size_string = "0" + hand_size_string;

	if (now_turn == true) {
		ConsoleConfig::SetColor(Color::BLACK, Color::LIGHTGRAY);
		ConsoleConfig::XYPrint(x, y, " " + name + " ");
		ConsoleConfig::XYPrint(x, y + 1, "  " + hand_size_string + "  ");
		ConsoleConfig::SetColor();
	}
	else {
		ConsoleConfig::XYPrint(x + 1, y, name);
		ConsoleConfig::XYPrint(x + 2, y + 1, hand_size_string);
	}
}