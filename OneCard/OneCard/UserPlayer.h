#pragma once
#include "Player.h"


class UserPlayer : public Player {
public:
	UserPlayer(string name, IDrawTop& deck);
	Action SelectAction(const Field& ref_field) const;
	Trump SelectSevenEvent();
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



Trump UserPlayer::SelectSevenEvent() {
	Key input = CS::GetKey();
	switch (input) {
	case KEY_1: return Trump::SPADE;
	case KEY_2: return Trump::CLOVER;
	case KEY_3: return Trump::HEART;
	case KEY_4: return Trump::DIAMOND;
	case KEY_S: SortHand();

	default: return SelectSevenEvent();
	}
}
