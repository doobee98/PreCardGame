#pragma once
#include "Player.h"


class AIPlayer : public Player {
public:
	AIPlayer(string name, IDrawTop& deck);
	Key SelectAction() const;
};

AIPlayer::AIPlayer(string name, IDrawTop& deck) : Player(name, deck) {

}

Key AIPlayer::SelectAction() const {
	return Key::KEY_UNDEFINED;
}