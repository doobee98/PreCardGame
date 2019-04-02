#pragma once
#include "Player.h"


class AIPlayer : public Player {
public:
	AIPlayer(string name, IDrawTop& deck);
	Action SelectAction(const Field& ref_field) const;
};

AIPlayer::AIPlayer(string name, IDrawTop& deck) : Player(name, deck) {

}

Action AIPlayer::SelectAction(const Field& ref_field) const {
	CS::GetKey();
	return Action::DRAW;
}