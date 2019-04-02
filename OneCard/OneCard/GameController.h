#pragma once
#include <iostream>
#include <deque>
#include "UserPlayer.h"
#include "AIPlayer.h"
#include "Deck.h"
#include "Field.h"
#include "TurnSystem.h"
#include "IOController.h"
using namespace std;


class GameController {
private:
	static GameController* instance;
	GameController();
	~GameController();
	
	deque<Player*> players;
	Field field;
	Deck deck;
	TurnSystem& turn;

	IOController io;

public:
	static GameController& GetInstance();
	void Init();
	void Run();
};



GameController* GameController::instance = NULL;

GameController& GameController::GetInstance() {
	if (instance == NULL) 
		instance = new GameController();
	
	return *instance;
}

GameController::GameController() 
	: players(), field(), deck(field), turn(TurnSystem::GetInstance()), io(players, deck, field) {

}

GameController::~GameController() {
	auto iter = players.begin();
	for (; iter != players.end(); iter++)
		delete *iter;
}


void GameController::Init() {
	int player_num = io.InitAndGetPlayerNum();
	turn.SetMaxPlayerNum(player_num);

	players.push_back(new UserPlayer("User", deck));
	players.back()->Draw(5);

	for (int i = 1; i < player_num; i++) {
		players.push_back(new AIPlayer("AI@" + to_string(i), deck));
		players.back()->Draw(5);
	}

	field.PlayCard(deck.DrawTop());
	field.NotifySpecial();
	field.ResetDrawStack();
}


void GameController::Run() {
	Init();

	auto iter = players.begin();

	while (true) {
		iter = turn.NextPlayer(iter);
		Player& now_player = **iter;
		io.UserScreen();
		now_player.SelectAction();
		Key choice = CS::GetKey(); // io에서 getkey와 관련된 함수 만들기
		
		//draw
		now_player.Draw(field.GetDrawStack());
		field.ResetDrawStack();

		//playcard
		field.PlayCard(now_player.PopHandCard(0));
			switch (field.NotifySpecial()) {
			case Notice::JACK: turn.PlayJ();  break;
			case Notice::QUEEN: turn.PlayQ(); break;
			case Notice::KING: turn.PlayK(); break;
			case Notice::SEVEN: io.SevenEvent();
			default: turn.PlayDefault(); // case NONE:
		}

		//sort
		now_player.SortHand();

		//check game end
	}
}