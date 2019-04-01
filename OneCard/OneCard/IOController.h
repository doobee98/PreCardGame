#pragma once
#include <iostream>
#include <deque>
#include "ConsoleConfig.h"
#include "ViewConfig.h"
#include "Player.h"
#include "IPrint.h"
namespace CS = ConsoleConfig;
namespace VW = ViewConfig;
using namespace std;


class IOController {
private:
	const deque<Player>& players; // deque<IPrint>&로 받는 방법이 있을까?
	const IPrint& deck;
	const IPrint& field;

public:
	IOController(const deque<Player>& players, const IPrint& deck, const IPrint& field);
	int Init() const; // Get Player Num
	void UserScreen() const;
	Key GetInput() const;
};



IOController::IOController(const deque<Player>& players, const IPrint& deck, const IPrint& field) :
	players(players), deck(deck), field(field) {
}

int IOController::Init() const {
	CS::XYPrint(5, 2, "Project OneCard SingleGame (Made by 2doo)");
	CS::XYPrint(5, 3, "How many AI players? (1 ~ 3) : ");

	int input;
	cin >> input;
	if (input >= 1 && input <= 3) 
		return input + 1;
	else {
		CS::Clrscr();
		CS::XYPrint(5, 1, "Range Off!");
		return Init();
	}
}


void IOController::UserScreen() const {
	CS::Clrscr();
	auto iter = players.begin();
	(*iter).Print(VW::USER::X, VW::USER::Y);
	iter++;
	for (int w = 0; iter != players.end(); iter++) {
		(*iter).Print(VW::AI_ALL::X + w, VW::AI_ALL::Y);
		w += VW::AI::WIDTH + 2;
	}
	
	deck.Print(VW::DECK::X, VW::DECK::Y);
	field.Print(VW::FIELD::X, VW::FIELD::Y);
}


Key IOController::GetInput() const {
	Key temp = CS::GetKey();
	if (temp >= Key::KEY_1 && temp <= Key::KEY_0) {// 1<= k <= 10
		//which act?
	}
	return Key::KEY_UNDEFINED;
}