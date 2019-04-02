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
	: players(), field(), deck(field), turn(TurnSystem::GetInstance()), io(players, deck, field, turn) {

}

GameController::~GameController() {
	auto iter = players.begin();
	for (; iter != players.end(); iter++)
		delete *iter;
}


void GameController::Init() {
	// 총 플레이어 인원 입력받기
	int player_num = io.InitAndGetPlayerNum();
	turn.SetMaxPlayerNum(player_num);

	// 유저 생성, 드로우
	players.push_back(new UserPlayer("User", deck));
	players.back()->Draw(5);

	// ai생성, 드로우
	for (int i = 1; i < player_num; i++) {
		players.push_back(new AIPlayer("Com" + to_string(i), deck));
		players.back()->Draw(5);
	}

	// 필드에 1장 오픈
	field.PlayCard(deck.DrawTop());
	field.NotifySpecial();
	field.ResetDrawStack();
}


void GameController::Run() {
	Init();

	auto iter = players.begin();

	while (true) {
		// 이번 턴 플레이어 결정
		iter = turn.NextPlayer(iter);
		Player& now_player = **iter;

		// 유저 사이드 스크린
		io.UserScreen();

		// 플레이어에게 행동 결정받기
		Action choice = now_player.SelectAction(field);

		// PlayCard
		if (choice >= HAND1 && choice <= HAND15) {
			field.PlayCard(now_player.PopHandCard(choice));
			switch (field.NotifySpecial()) {
			case Notice::JACK: turn.PlayJ();  break;
			case Notice::QUEEN: turn.PlayQ(); break;
			case Notice::KING: turn.PlayK(); break;
			case Notice::SEVEN: io.SevenEvent();
			default: turn.PlayDefault(); // case Notice::NONE:
			}
		}

		else {
			switch (choice) {
			case DRAW: 
				now_player.Draw(field.GetDrawStack());
				field.ResetDrawStack();
				turn.PlayDefault();
				break;
			case SORT:
				now_player.SortHand();
				continue;
			default:
				continue;
			}
		}
	
		//check game end
	}
}