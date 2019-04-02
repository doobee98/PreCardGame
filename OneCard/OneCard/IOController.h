#pragma once
#include <iostream>
#include <deque>
#include "ConsoleConfig.h"
#include "ViewConfig.h"
#include "Player.h"
#include "Field.h"
#include "UserPlayer.h"
#include "IPrint.h"
namespace CS = ConsoleConfig;
namespace VW = ViewConfig;
using namespace std;


class IOController {
private:
	const deque<Player*>& players; // deque<IPrint>&로 받는 방법이 있을까?
	const IPrint& deck;
	const Field& field;
	string log;

public:
	IOController(const deque<Player*>& players, const IPrint& deck, const Field& field);
	int InitAndGetPlayerNum() const; // Get Player Num
	void UserScreen() const;
	void SevenEvent() const;
	Key GetInput() const;

private:
	void PrintUserHand() const;
};



IOController::IOController(const deque<Player*>& players, const IPrint& deck, const Field& field) :
	players(players), deck(deck), field(field), log() { 
}

int IOController::InitAndGetPlayerNum() const {
	CS::XYPrint(5, 2, "Project OneCard SingleGame (Made by 2doo)");
	CS::XYPrint(5, 3, "How many AI players? (1 ~ 3) : ");

	int input;
	cin >> input;
	if (input >= 1 && input <= 3) 
		return input + 1;
	else {
		CS::Clrscr();
		CS::XYPrint(5, 1, "Range Off!");
		return InitAndGetPlayerNum();
	}
}


void IOController::UserScreen() const {
	CS::Clrscr();
	auto iter = players.begin();
	(**iter).Print(VW::USER::X, VW::USER::Y);
	iter++;
	for (int w = 0; iter != players.end(); iter++) {
		(**iter).Print(VW::AI_ALL::X + w, VW::AI_ALL::Y);
		w += VW::AI::WIDTH + 2;
	}
	
	deck.Print(VW::DECK::X, VW::DECK::Y);
	field.Print(VW::FIELD::X, VW::FIELD::Y);
	PrintUserHand();
}


void IOController::SevenEvent() const {

}


Key IOController::GetInput() const {
	Key temp = CS::GetKey();
	if (temp >= Key::KEY_1 && temp <= Key::KEY_0) { // 1<= k <= 10
		//which act?
	}
	return Key::KEY_UNDEFINED;
}


void IOController::PrintUserHand() const {
	const auto user_hand = players.at(0)->GetHand();
	
	auto iter = user_hand.begin();
	const int base_x = VW::USER_HAND::X;
	const int base_y = VW::USER_HAND::Y;
	int card_num = 1;

	for (int x = 0, y = 0; iter != user_hand.end(); x++, y++, iter++) {
		const Card* temp = *iter;
		CS::GotoXY(base_x + (x / VW::USER_HAND::ROW_NUM) * 10 , base_y + (y % VW::USER_HAND::ROW_NUM));
		cout.width(2); cout.fill(' ');
		if (field.CanPlayCard(temp))
			cout << card_num;
		else
			cout << "";
		++card_num;
		cout << " " << *temp;
	}
}