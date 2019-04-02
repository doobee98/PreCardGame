#pragma once
#include "Player.h"


class UserPlayer : public Player {
public:
	UserPlayer(string name, IDrawTop& deck);
	Action SelectAction(const Field& ref_field) const;
};


UserPlayer::UserPlayer(string name, IDrawTop& deck) : Player(name, deck){ 
	
}

Action UserPlayer::SelectAction(const Field& ref_field) const {
	Key input = CS::GetKey();
	if (input >= KEY_1 && input <= KEY_T) {
		int num = input - KEY_1;
		if(num >= GetHand().size())
			return ACT_UNDEFINED;
		else if (ref_field.CanPlayCard(GetHand().at(num)))
			return (Action)num;
		else
			return ACT_UNDEFINED;
	}
	else {
		switch (input) {
		case KEY_S: return SORT; case KEY_D: return DRAW;
		default: return ACT_UNDEFINED;
		}
	}
}

