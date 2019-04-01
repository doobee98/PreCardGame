#pragma once
#include <string>

enum Trump {
	SPADE, CLOVER, HEART, DIAMOND, JOKER_TRP
};

enum Number {
	A = 1, NUM_2, NUM_3, NUM_4, NUM_5,
	NUM_6, NUM_7, NUM_8, NUM_9, NUM_10,
	J, Q, K, JOKER_NUM
};

enum Attack {
	ACE = 3, TWO = 2, JOKER = 5, UNDEFINED = 0
	// if Attack Value == 1, invalid
};



namespace CardConfig {
	const std::string TrumpToString(Trump t) {
		switch (t) {
		case SPADE: return "¢¼";
		case CLOVER: return "¢À";
		case HEART:  return "¢¾";
		case DIAMOND: return "¡ß";
		default: return "¡Ú";
		}
	}

	const Attack NumToAtk(Number num) {
		switch (num) {
		case Number::A: return Attack::ACE;
		case Number::NUM_2: return Attack::TWO;
		case Number::JOKER_NUM: return Attack::JOKER;
		default: return Attack::UNDEFINED;
		}
	}
};