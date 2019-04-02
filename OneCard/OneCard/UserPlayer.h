#pragma once
#include "Player.h"


class UserPlayer : public Player {
public:
	UserPlayer(string name, IDrawTop& deck);
	Key SelectAction() const;
};


UserPlayer::UserPlayer(string name, IDrawTop& deck) : Player(name, deck){ 
	
}

Key UserPlayer::SelectAction() const {
	return Key::KEY_UNDEFINED;
}

