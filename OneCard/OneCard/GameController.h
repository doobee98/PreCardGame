#pragma once
#include <iostream>
#include <deque>
#include "UserPlayer.h"
#include "AIPlayer.h"
#include "Deck.h"
#include "Field.h"
#include "TurnSystem.h"
#include "Timer.h"
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
	Timer timer;

	ViewController view;

public:
	static GameController& GetInstance();
	void Init();
	void Run();

private:
	Trump SevenEvent(Player& now_player);
	const Player* CheckEnd() const;
	string MakePlayingLog(const Player& now_player, const Card* playing_card);
};



GameController* GameController::instance = NULL;

GameController& GameController::GetInstance() {
	if (instance == NULL) 
		instance = new GameController();
	
	return *instance;
}

GameController::GameController() 
	: players(), 
	field(), 
	deck(field), 
	turn(TurnSystem::GetInstance()), 
	timer(), 
	view(players, deck, field, turn, timer) {

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
	timer.ResetTimer();

	while (true) {
		// 이번 턴 플레이어 결정
		iter = turn.NextPlayer(iter);
		Player& now_player = **iter;

		// 유저 사이드 스크린
		view.UserScreen();

		if (_kbhit()) {
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
					Trump choice_trump = SevenEvent(now_player);
					field.SetLead(choice_trump, Number::NUM_7);
					view.UpdateLog(now_player.GetName() + " changes lead trump.");
				}
				default: turn.PlayDefault(); // case Notice::NONE:
				}

				timer.ResetTimer();
			}

			// Draw, Sort, etc
			else {
				switch (choice) {
				case DRAW: {
					int num = field.GetDrawStack();
					now_player.Draw(num);
					field.ResetDrawStack();
					turn.PlayDefault();
					timer.ResetTimer();
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
		}

		else if(timer.IsTimerOver()){
			// 타이머 종료시 까지 다른 액션이 없다면 강제로 드로우
			int num = field.GetDrawStack();
			now_player.Draw(num);
			field.ResetDrawStack();
			turn.PlayDefault();
			view.UpdateLog(now_player.GetName() + " draws " + to_string(num) + " cards.");
			timer.ResetTimer();
		}

		if (CheckEnd() != NULL)
			break;

		Sleep(20);
	}

	const Player& winner = *CheckEnd(); // const 함수여서 다시 호출하여도 같은 값
	view.UpdateLog("Winner : " + winner.GetName() + "!");
	view.UserScreen();
	ConsoleConfig::GetKey();
}


Trump GameController::SevenEvent(Player& now_player) {
	view.UpdateLog("1. Spade, 2. Clover, \n 3. Heart, 4. Diamond");
	
	while (true) {
		view.UserScreen();

		if (_kbhit()) {
			Key input = now_player.SelectSevenEvent();
			switch (input) {
			case KEY_1: return SPADE;
			case KEY_2: return CLOVER;
			case KEY_3: return HEART;
			case KEY_4: return DIAMOND;
			default: break;
			}
		}

		else if (timer.IsTimerOver()) {
			return (Trump)(rand() % 4 + 1);
		}

		Sleep(20);
	}



	while (_kbhit() || timer.IsTimerOver() ) {
		view.UserScreen();
		Sleep(20);
	}
}


const Player* GameController::CheckEnd() const {
	auto iter = players.begin();
	for (; iter != players.end(); iter++) 
		if ((**iter).GetHand().size() == 0)
			return *iter;
	
	return NULL;
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