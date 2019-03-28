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
	Deck deck;
	Field field;
	TurnSystem& tsys;


	GameController(int player_num);
	~GameController();

public:
	static GameController& GetInstance(int player_num);
	void Run();

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
	// players에 pair를 넣는 순서를 랜덤으로 하면, 시작 플레이어를 랜덤으로 할 수 있음

}


GameController::~GameController() {

}


void GameController::Run() {
	auto iter = players.begin();

	while (true) {
		Player& now_player = (*iter).first;
		PlayerController& now_player_controller = (*iter).second;
		
		// UseHand, Draw, Sort (Sort는 Controller에서 처리)
		// 불가능한 UseHand는 IO 컨트롤러에서 처리하기
		// Exclaim OneCard는 메소드를 따로 둠
		int choice = now_player_controller.SelectAction();
		switch (choice) {
		case 1: // magic number. enum으로 바꿔야함
			now_player.Draw(field.GetDrawStack()); 
			field.ResetDrawStack();
			break;
		case 2:
			now_player.UseHand(); break;
		default:
			break;
		}


		iter = players.begin() + tsys.NextPlayer();
	}

}


void GameController::InitializeGame() {
//	srand((unsigned int)time(NULL)); // for Deck::RandomizeDeck

	for (auto iter = players.begin(); iter != players.end(); iter++)
		(*iter).first.Draw(START_DRAW_SIZE);

	field.PlayCard(deck.DrawTop());
	field.ResetDrawStack();
}
