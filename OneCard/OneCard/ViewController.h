#pragma once
#include <iostream>
#include <deque>
#include "ConsoleConfig.h"
#include "ViewConfig.h"
#include "Player.h"
#include "Field.h"
#include "IPrint.h"
#include "TurnSystem.h"
#include "Timer.h"
namespace CS = ConsoleConfig;
namespace VW = ViewConfig;
using namespace std;


class ViewController {
private:
	const deque<Player*>& players; // deque<IPrint>&로 받는 방법이 있을까?
	const IPrint& deck;
	const Field& field; // field.CanPlayCard와 field.Print를 사용해야 함
	const TurnSystem& turn;
	const Timer& timer;
	string log; // log 출력하기

public:
	ViewController(const deque<Player*>& players, const IPrint& deck, const Field& field, const TurnSystem& turn, const Timer& timer);
	~ViewController();
	int InitAndGetPlayerNum() const; // Get Player Num
	void UserScreen() const;
	void UpdateLog(const string s);

private:
	void PrintUserHand() const;
};



ViewController::ViewController(const deque<Player*>& players, const IPrint& deck, const Field& field, const TurnSystem& turn, const Timer& timer) :
	players(players), 
	deck(deck), 
	field(field), 
	turn(turn), 
	timer(timer), 
	log("Start Game!") { 
}

ViewController::~ViewController() {
	CS::ConsoleClose();
}

int ViewController::InitAndGetPlayerNum() const {
	CS::ConsoleStart();

	while (true) {
		CS::XYPrint(5, 2, "Project OneCard SingleGame (Made by 2doo)");
		CS::XYPrint(5, 3, "How many AI players? (1 ~ 3) : ");
		CS::ConsoleActiveScreen();

		Key input = CS::GetKey();

		if (input >= KEY_1 && input <= KEY_3)
			return input + 2; // KEY DIFF : 1, USER PLAYER : 1 TOTAL 2
		else {
			CS::Clrscr();
			CS::XYPrint(5, 1, "Range Off!");
		}
	}
}


void ViewController::UserScreen() const {
	CS::Clrscr();

	// Print User
	auto iter = players.begin();
	(**iter).Print(VW::USER::X, VW::USER::Y);
	iter++;

	// Print Com
	for (int w = 0; iter != players.end(); iter++) {
		(**iter).Print(VW::AI_ALL::X + w, VW::AI_ALL::Y);
		w += VW::AI::WIDTH + 2;
	}

	//Print Log
	CS::XYPrint(VW::LOG::X, VW::LOG::Y, log);
	
	//Print Turn Direction
	string dir_string = turn.GetDirection() == Direction::CLOCKWISE ? "--->" : "<---";
	CS::XYPrint(VW::TURNDIR::X, VW::TURNDIR::Y, dir_string);

	// Print Deck Info : left cards num
	deck.Print(VW::DECK::X, VW::DECK::Y);

	// Print Field Info : Open Card, Lead Trump, Atk Stack
	field.Print(VW::FIELD::X, VW::FIELD::Y);

	// Print Timer
	timer.Print(VW::TIMER::X, VW::TIMER::Y);

	//Print User Hand;
	PrintUserHand();


	// Active ScreenBuffer
	CS::ConsoleActiveScreen();
}


void ViewController::UpdateLog(const string s) {
	log = s;
}


void ViewController::PrintUserHand() const {
	const auto user_hand = players.at(0)->GetHand();
	auto iter = user_hand.begin();
	const int base_x = VW::USER_HAND::X;
	const int base_y = VW::USER_HAND::Y;
	int card_num = 1;

	for (int x = 0, y = 0; iter != user_hand.end(); x++, y++, iter++) {
		const Card* temp = *iter;
		int _x = base_x + (x / VW::USER_HAND::ROW_NUM) * 9;
		int _y = base_y + (y % VW::USER_HAND::ROW_NUM);

		if (field.CanPlayCard(temp)) {
			switch (card_num) {
			case 10: CS::XYPrint(_x, _y, "0"); break;
			case 11: CS::XYPrint(_x, _y, "Q"); break;
			case 12: CS::XYPrint(_x, _y, "W"); break;
			case 13: CS::XYPrint(_x, _y, "E"); break;
			case 14: CS::XYPrint(_x, _y, "R"); break;
			case 15: CS::XYPrint(_x, _y, "T"); break;
			default: CS::XYPrint(_x, _y, to_string(card_num)); break;
			}
		}

		++card_num;
		temp->Print(_x + 2, _y);
	}
}