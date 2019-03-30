#pragma once
#include <utility>
#include "Player.h"
#include "PlayerController.h"
#include "Deck.h"
#include "Field.h"
#include "TurnSystem.h"
using namespace std;


class GameController {
	static GameController* instance;
private:
	deque < pair <Player, PlayerController> > players;
	Field field;
	Deck deck;
	TurnSystem& tsys;


	GameController(int player_num);
	~GameController();

public:
	static GameController& GetInstance(int player_num);
	void Run();
	void TestViewGame();

private:
	void InitializeGame();
};




GameController* GameController::instance = NULL;
GameController& GameController::GetInstance(int player_num = 0) {
	if (instance == NULL) {
		if (player_num == 0)
			throw "GameController::GetInstance : 초기화 오류";
		instance = new GameController(player_num);
	}
	return *instance;
}


GameController::GameController(int player_num) : field(), deck(field), tsys(TurnSystem::GetInstance(player_num)) {
	if (player_num < 2 && player_num > 5)
		throw "GameController::GameController : Invalid Player Num - n should be in range 2 <= n <= 5";

	players.push_back(make_pair(Player("You", deck), PlayerController()));
	player_num--;

	for (int i = 1; i <= player_num; i++) 
		players.push_back(make_pair(Player("AI@" + to_string(i), deck), PlayerController()));
	
}


GameController::~GameController() {

}


void GameController::Run() {
	InitializeGame();
	auto iter = players.begin(); // 시작 iter 참조 위치를 랜덤으로 -> 시작 플레이어를 랜덤으로

	while (true) {
		Player& now_player = (*iter).first;
		PlayerController& now_player_controller = (*iter).second;
		
		// UseHand, Draw, Sort
		// 불가능한 UseHand는 IO에서 처리하기
		// Exclaim OneCard는 메소드를 따로 둠
		int choice = now_player_controller.SelectAction();
		if (choice == Action::DRAW) {
			now_player.Draw(field.GetDrawStack());
			field.ResetDrawStack();
		}
		else if (choice == Action::SORT) {
			now_player.SortHand();
			continue; // hand를sort하고 다시 while문의 맨 처음으로 돌아감
		}
		else if (choice >= 1 && choice <= MAX_HAND) { // HAND
			field.PlayCard(now_player.ChooseHand(choice));
		}
		else { // choice == UNDEFINED
			throw "GameController::Run : Choice 값이 Undefined입니다.";
		}

		iter = players.begin() + tsys.NextPlayer(field);
	}

}


void GameController::InitializeGame() {

	for (auto iter = players.begin(); iter != players.end(); iter++)
		(*iter).first.Draw(START_DRAW_SIZE);

	field.PlayCard(deck.DrawTop());
	field.ResetDrawStack();
}



void GameController::TestViewGame() {
	InitializeGame();
	cout << "OpenCard : ";
	cout << *(field.GetOpenCard()) << endl;
	for (auto iter = players.begin(); iter != players.end(); iter++) {
		Player& now_player = (*iter).first;
		PlayerController& now_player_controller = (*iter).second;

		now_player.TestViewHand();
	}
}
