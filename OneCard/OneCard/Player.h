#pragma once
#include <deque>
#include <algorithm>
#include "Card.h"
#include "IPrint.h"
#include "IDrawTop.h"

#ifndef interface
#define interface class
#endif

enum {

};


interface Player : public IPrint {
private:
	string name;
	deque<const Card*> hand;
	bool now_turn;
	IDrawTop& ref_deck;

public:
	Player(string name, IDrawTop& deck);
	void Draw(int num);
	const Card* PopHandCard(int num);
	void SortHand();
	const deque<const Card*>& GetHand() const;
	virtual Key SelectAction() const = 0;
	void SetNowTurn(bool value);
	void Print(int x, int y) const;
};

Player::Player(string name, IDrawTop& deck) : name(name), hand(), now_turn(false), ref_deck(deck) {

}

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
	ConsoleConfig::XYPrint(x + 1, y, name);
	ConsoleConfig::XYPrint(x, y + 1, (now_turn == true) ? "N" : "W");
	ConsoleConfig::XYPrint(x + 4, y + 1, to_string(hand.size()));
}