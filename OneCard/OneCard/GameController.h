#pragma once
#include <iostream>
#include <deque>
#include "UserPlayer.h"
#include "AIPlayer.h"
#include "Deck.h"
#include "Field.h"
#include "TurnSystem.h"
#include "ViewController.h"
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

	ViewController view;

public:
	static GameController& GetInstance();
	void Init();
	void Run();

private:
	void SevenEvent();
	string MakePlayingLog(const Player& now_player, const Card* playing_card);
};



GameController* GameController::instance = NULL;

GameController& GameController::GetInstance() {
	if (instance == NULL) 
		instance = new GameController();
	
	return *instance;
}

GameController::GameController() 
	: players(), field(), deck(field), turn(TurnSystem::GetInstance()), view(players, deck, field, turn) {

}

GameController::~GameController() {
	auto iter = players.begin();
	for (; iter != players.end(); iter++)
		delete *iter;
}


void GameController::Init() {
	// 총 플레이어 인원 입력받기
	int player_num = view.InitAndGetPlayerNum();
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
		view.UserScreen();

		// 필드를 본 플레이어에게 행동 결정받기
		Action choice = now_player.SelectAction(field);

		// PlayCard
		if (choice >= HAND1 && choice <= HAND15) {
			const Card* playing_card = now_player.PopHandCard(choice);
			field.PlayCard(playing_card);
			view.UpdateLog(MakePlayingLog(static_cast<const Player&>(now_player), playing_card));
			switch (field.NotifySpecial()) {
			case Notice::JACK: turn.PlayJ();  break;
			case Notice::QUEEN: turn.PlayQ(); break;
			case Notice::KING: turn.PlayK(); break;
			case Notice::SEVEN: {
				SevenEvent();
				Trump choice_trump = now_player.SelectSevenEvent();
				field.SetLead(choice_trump, Number::NUM_7);
				view.UpdateLog(now_player.GetName() + " changes lead trump.");
			}
			default: turn.PlayDefault(); // case Notice::NONE:
			}
		}

		// Draw, Sort, etc
		else {
			switch (choice) {
			case DRAW: {
				int num = field.GetDrawStack();
				now_player.Draw(num);
				field.ResetDrawStack();
				turn.PlayDefault();
				view.UpdateLog(now_player.GetName() + " draws " + to_string(num) + " cards.");
				break;
			}
			case SORT:
				now_player.SortHand();
				continue; // 턴이 바뀌지 않은 채로 userscreen을 다시 띄운다.
			default:
				continue;
			}
		}
	
		//check game end
	}
}


void GameController::SevenEvent() {
	view.UpdateLog("1. Spade, 2. Clover, \n 3. Heart, 4. Diamond");
	view.UserScreen();
}


string GameController::MakePlayingLog(const Player& now_player, const Card* playing_card) {
	const string& name = now_player.GetName();

	Trump t = playing_card->GetTrump();
	Number n = playing_card->GetNumber();
	string card_string;

	if (t == JOKER_TRP)
		card_string = "JOKER";
	else {
		switch (t) {
		case SPADE: card_string += "Spade "; break;
		case CLOVER: card_string += "Clover "; break;
		case HEART: card_string += "Heart "; break;
		case DIAMOND: card_string += "Diamond "; break;
		default: break;
		}
		switch (n) {
		case A: card_string += "A"; break;
		case J: card_string += "J"; break;
		case Q: card_string += "Q"; break;
		case K: card_string += "K"; break;
		default: card_string += to_string(n);
		}
	}

	return name + " plays " + card_string + ".";
}