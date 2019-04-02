#pragma once
#include <iostream>
#include <deque>
#include "ConsoleConfig.h"
#include "ViewConfig.h"
#include "Player.h"
#include "Field.h"
#include "IPrint.h"
#include "TurnSystem.h"
namespace CS = ConsoleConfig;
namespace VW = ViewConfig;
using namespace std;


class IOController {
private:
	const deque<Player*>& players; // deque<IPrint>&로 받는 방법이 있을까?
	const IPrint& deck;
	const Field& field; // field.CanPlayCard와 field.Print를 사용해야 함
	const TurnSystem& turn;
	string log; // log 출력하기

public:
	IOController(const deque<Player*>& players, const IPrint& deck, const Field& field, const TurnSystem& turn);
	int InitAndGetPlayerNum() const; // Get Player Num
	void UserScreen() const;
	void SevenEvent() const;

private:
	void PrintUserHand() const;
};



IOController::IOController(const deque<Player*>& players, const IPrint& deck, const Field& field, const TurnSystem& turn) :
	players(players), deck(deck), field(field), turn(turn), log() { 
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
	
	string dir_string = turn.GetDirection() == Direction::CLOCKWISE ? "--->" : "<---";
	CS::XYPrint(VW::TURNDIR::X, VW::TURNDIR::Y, dir_string);
	deck.Print(VW::DECK::X, VW::DECK::Y);
	field.Print(VW::FIELD::X, VW::FIELD::Y);
	PrintUserHand();
}


void IOController::SevenEvent() const {

}


void IOController::PrintUserHand() const {
	const auto user_hand = players.at(0)->GetHand();
	
	auto iter = user_hand.begin();
	const int base_x = VW::USER_HAND::X;
	const int base_y = VW::USER_HAND::Y;
	int card_num = 1;

	for (int x = 0, y = 0; iter != user_hand.end(); x++, y++, iter++) {
		const Card* temp = *iter;
		CS::GotoXY(base_x + (x / VW::USER_HAND::ROW_NUM) * 9 , base_y + (y % VW::USER_HAND::ROW_NUM));
		if (field.CanPlayCard(temp)) {
			switch (card_num) {
			case 10: cout << '0'; break;
			case 11: cout << 'Q'; break;
			case 12: cout << 'W'; break;
			case 13: cout << 'E'; break;
			case 14: cout << 'R'; break;
			case 15: cout << 'T'; break;
			default: cout << card_num; break;
			}
		}
		else
			cout << ' ';
		++card_num;
		cout << " " << *temp;
	}
}