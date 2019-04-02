#pragma once
#include "Player.h"
#include "cstdlib"
#include "ctime"


class AIPlayer : public Player {
public:
	AIPlayer(string name, IDrawTop& deck);
	Action SelectAction(const Field& ref_field) const;
	Trump SelectSevenEvent();
};






AIPlayer::AIPlayer(string name, IDrawTop& deck) : Player(name, deck) {
	srand((unsigned int)time(NULL));
}

Action AIPlayer::SelectAction(const Field& ref_field) const {
	CS::GetKey(); // 시간제한이 아직 없으므로 wait하도록 함
	/*
	AI 메커니즘 SelectAction ver 1.0
	0. 일단 sort - !!! 안됨, sort가 const 메소드가 아님
	1. hand에서 사용 가능한 카드를 usable_card추림
	-> 1-1. usable_card.size()가 0이라면 Action::DRAW 반환
	2. 그 카드 중 랜덤으로 반환
	*/

	const deque<const Card*> _hand = GetHand();
	deque<Action> usable_card;
	
	int index = 0;
	for (auto iter = _hand.begin(); iter != _hand.end(); iter++, index++) {
		if (ref_field.CanPlayCard(*iter))
			usable_card.push_back((Action)index);
	}

	if (usable_card.size() == 0)
		return Action::DRAW;

	return usable_card.at(rand() % usable_card.size());
}


Trump AIPlayer::SelectSevenEvent(){
	CS::GetKey(); // 시간제한이 아직 없으므로 wait하도록 함
	/*
	AI 메커니즘 SelectSeven ver 1.0
	1. 넷 중 랜덤으로 반환
	*/
	return (Trump)(rand() % 4 + 1);
}