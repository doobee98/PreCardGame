#pragma once
#include <iostream>
#include <deque>
#include "Player.h"
#include "Deck.h"
#include "Field.h"
#include "TurnSystem.h"
#include "IOController.h"
using namespace std;


class GameController {
private:
	static GameController* instance;
	GameController();
	
	deque<Player> players;
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


void GameController::Init() {
	int player_num = io.Init();
	for (int i = 0; i < player_num; i++) {
		players.push_back(Player());
//		players.back().Draw(5);
	}

	field.PlayCard(deck.DrawTop());
	field.ResetDrawStack();
}


void GameController::Run() {
	Init();

	auto iter = players.begin();

	while (true) {
		//next player choose -> move iter by turnsystem : turn
		Player now_player = *iter;
		io.UserScreen();
//		now_player.SelectAction();
		Key choice = CS::GetKey(); // io에서 getkey와 관련된 함수 만들기
		
		//draw
		//now_player.AddHand(deck.DrawTop());
		//playcard
		//field.PlayCard(now_player.UseCard()); - if seven card played?
		//sort
		//now_player.SortHand();

		//check game end
	}
}