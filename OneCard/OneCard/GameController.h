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
#include "CircularNode.h"
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
	bool CheckEnd();
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
	timer(RuleConfig::BASE_TIMER), 
	view(players, deck, field, turn, timer) {

}

GameController::~GameController() {
	// Player 포인터 메모리 해제
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

	// active_player deque를 참조자로 선언하여 따로 만들어줌
	// 파산하여 Lose한 플레이어를 active player에서 제외하여 플레이하기 위해서
	deque< CircularNode<Player*> > active_players;
	for (auto iter = players.begin(); iter != players.end(); iter++) 
		active_players.push_back(CircularNode<Player*>(*iter));

	int temp_size = active_players.size();
	for (int i = 0; i < temp_size; i++) {
		active_players.at(i).prev = &(active_players.at((i - 1 + temp_size) % temp_size));
		active_players.at(i).next = &(active_players.at((i + 1) % temp_size));
	}


	//auto iter = active_players.begin();
	CircularNode<Player*>* cir_iter = &(active_players.at(0));
	timer.ResetTimer();

	// 매턴 while문 한바퀴
	while (true) {

		// 이번 턴 플레이어 결정
		cir_iter = turn.NextPlayer(cir_iter);
		Player& now_player = **cir_iter;

		// 유저 사이드 스크린
		view.UserScreen();

		
			// 필드를 본 플레이어에게 행동 결정받기
			Action choice = now_player.SelectAction(field);

			// PlayCard
			if (choice >= HAND1 && choice <= HAND15) {
				const Card* playing_card = now_player.PopHandCard(choice);
				field.PlayCard(playing_card);
				view.UpdateLog(MakePlayingLog(static_cast<const Player&>(now_player), playing_card));

				// 카드를 냈는데 남은 카드가 없다면 status를 win으로 수정하고 반복문 탈출 (게임 종료)
				if (now_player.GetHand().size() == 0) {
					now_player.SetStatus(Player_Status::WIN);
					break; // while(true) 탈출 문장
				}
				
				else {
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
			}

			// Draw, Sort, etc
			else {
				switch (choice) {
				case DRAW: {
					int draw_num = field.GetDrawStack();
					now_player.Draw(draw_num);
					field.ResetDrawStack();
					turn.PlayDefault();
					timer.ResetTimer();

					// 카드를 드로우했는데 hand_max_card를 넘을 경우 파산으로 취급하고 게임에서 제외함
					if (now_player.GetHand().size() >= RuleConfig::BASE_MAX_HAND) {
						now_player.SetStatus(Player_Status::LOSE);
						// 들고 있던 카드를 모두 반납
						auto lose_hand = now_player.GetHand();
						for(auto iter = lose_hand.begin(); iter != lose_hand.end(); iter++)
							deck.AddCard(*iter);		
						
						now_player.ClearHand();

						// 없어지는 플레이어의 다음 턴 플레이어를 지정
						(*cir_iter).next->prev = (*cir_iter).prev;
						(*cir_iter).prev->next = (*cir_iter).next;
						view.UpdateLog(now_player.GetName() + " BANKRUPT!");
					}
					else {
						view.UpdateLog(now_player.GetName() + " draws " + to_string(draw_num) + " cards.");
					}
					break;
				}
				case SORT:
					// sort는 타이머를 리셋하지 않고, hand만 sort하고 다시 기다림
					now_player.SortHand();
					break;

				default: break;
				}
			}
		

		if(timer.IsTimerOver()){
			// 타이머 종료시 까지 다른 액션이 없다면 강제로 드로우
			// case DRAW: 와 같음
			int draw_num = field.GetDrawStack();
			now_player.Draw(draw_num);
			field.ResetDrawStack();
			turn.PlayDefault();
			timer.ResetTimer();
			view.UpdateLog(now_player.GetName() + " draws " + to_string(draw_num) + " cards.");
		}	

		if (CheckEnd() == true)
			break;

		Sleep(20);
	}


	//winner를 찾아 winner 선언후 run 종료
	for (auto iter = players.begin(); iter != players.end(); iter++) {
		if ((**iter).GetStatus() == Player_Status::WIN) {
			const Player& winner = **iter;
			view.UpdateLog("Winner : " + winner.GetName() + "!");
			view.UserScreen();
			ConsoleConfig::GetKey();

			return;
		}
	}

	// return이 되지 않은 경우 winner가 존재하지 않는 경우이므로 논리적 버그
	throw "GameController::Run - winner가 존재하지 않습니다.";
}


Trump GameController::SevenEvent(Player& now_player) {
	view.UpdateLog("1. Spade, 2. Clover, \n 3. Heart, 4. Diamond");
	
	while (true) {
		view.UserScreen();
		
		Key input = now_player.SelectSevenEvent();
		switch (input) {
		case KEY_1: return SPADE;
		case KEY_2: return CLOVER;
		case KEY_3: return HEART;
		case KEY_4: return DIAMOND;
		default: break;
		}

		if (timer.IsTimerOver()) {
			return (Trump)(rand() % 4 + 1);
		}

		Sleep(20);
	}
}


bool GameController::CheckEnd(){
	int playing_player_num = 0;
	for (auto iter = players.begin(); iter != players.end(); iter++) {
		if ((**iter).GetStatus() == Player_Status::WIN)
			return true;
		else if ((**iter).GetStatus() == Player_Status::PLAYING)
			playing_player_num++;
	}

	// 플레이 하는 인원이 1명이면(나머지 플레이어가 모두 탈락했으면) 게임 종료
	if (playing_player_num != 1) return false;
	else {
		for (auto iter = players.begin(); iter != players.end(); iter++) {
			if ((**iter).GetStatus() == Player_Status::PLAYING) {
				(**iter).SetStatus(Player_Status::WIN);
				return true;
			}
		}
	}
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